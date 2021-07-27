#include "stdafx.h"
#include "ResultScene.h"
#include "Player.h"
#include "TitleScene.h"
#include "UIDisplay.h"
#include "GameScene.h"
#include "BackGround.h"
#include "GimmickNeedle.h"
#include "SelectScene.h"
#include "TitleBack.h"
#include "GameTimer.h"
#include "BalloonAir.h"

namespace
{
	const Vector3 CAMERA_TARGET_POSITION = { 0.0f,100.0f, 0.0f };
	const Vector2 GAMESET_FONT_POSITION = { -200.0f,0.0f };
	const Vector2 WIN_FONT_POSITION = { -300.0f,0.0f };
	const Vector2 DRAW_FONT_POSITION = { -70.0f,0.0f };

	const int GAMESET_FONT_SCALE = 2;
	const float PLAYER_FONT_SCALE = 1.5f;
	const int GAMESET_FONT_OFFSET = 3;
	const float VALUE_MULTIPLY_IN_SPEED = 1.05f;//カメラスピードに欠ける値
	const int CAMERA_SHORTEST_RANGE = -500;
	const int CURSOR_SPRITE_WIDTH = 64;
	const int CURSOR_SPRITE_HEIGHT = 28;
	const int CURSOR_SPEED = 0.1f;
}

ResultScene::~ResultScene()
{
	
	DeleteGO(m_retriFontRender);
	DeleteGO(m_backMenuFontRender);
	DeleteGO(m_backTitleFontRender);
	DeleteGO(m_cursorSprite);
	DeleteGO(m_resultBGM);
}

bool ResultScene::Start()
{
	m_BG = FindGO<BackGround>("backGround");//バックグラウンドを参照
	m_gameScene = FindGO<GameScene>("gameScene");//ゲームシーンを参照
	//ゲームセットか、タイムアップを表示する
	m_gameSetFontRender = NewGO<FontRender>(0);
	m_gameSetFontRender->SetPosition({ GAMESET_FONT_POSITION });
	m_gameSetFontRender->SetScale(GAMESET_FONT_SCALE);
	m_gameSetFontRender->SetShadowFlag(true);
	m_gameSetFontRender->SetShadowOffset(GAMESET_FONT_OFFSET);
	m_gameSetFontRender->SetShadowColor({ Vector4::Black });

	if (m_resultState == enGameSet)
		m_gameSetFontRender->SetText(L"GAME SET");
	else if (m_resultState == enTimeUp)
		m_gameSetFontRender->SetText(L"TIME  UP");
	else 
		m_gameSetFontRender->SetText(L"H O  G E");
	//空気クラスを消す
	QueryGOs<BalloonAir>("balloonAir", [this](BalloonAir* balloonAir)->bool {
		DeleteGO(balloonAir);
		return true;
		});
	return true;
}
void ResultScene::Update()
{
	switch (m_resultState)
	{
	case enGameSet:
		GameSet();//決着がついたとき、もしくは同時に死んだとき
		break;		
	case enZoomWinner://勝者にカメラが寄る
		ZoomWinner();
		break;
	case enTimeUp://時間切れ
		TimeUp();
		break;
	case enDraw://勝者がいないとき
		Draw();
		break;
	case enMenu://メニュー選択
		Menu();
		break;
	}
}

//ゲームに決着がついた時、もしくは同時に死んだときの処理
void ResultScene::GameSet()
{
	if (m_gameSetDisplayedTime > 0)//ゲームセットフォントが表示されている間
	{
		m_gameSetDisplayedTime--;
		return;
	}
	else
	{
		if (m_winnerPl != nullptr)//勝者がいるとき
		{			
			DeleteGO(m_gameSetFontRender);//フォントを消す
			//勝者のプレイヤー番号を表示する
			m_winFontRender = NewGO<FontRender>(0);				
			m_winFontRender->SetScale(GAMESET_FONT_SCALE);
			m_winFontRender->SetText(L"PLAYER " + std::to_wstring(m_winnerPl->GetPlayerNum() + 1) + L" WIN!!");
			m_winFontRender->SetPosition({ WIN_FONT_POSITION });
			m_winFontRender->SetShadowFlag(true);
			m_winFontRender->SetShadowOffset(GAMESET_FONT_OFFSET);
			m_winFontRender->SetShadowColor({ m_winnerPl->GetPlColor() });

			m_winnerPl->SetPosition(m_winnerPos);//勝者用の位置に設定する
			m_winnerPl->SetMoveSpeed(Vector3::Zero);//スピードをゼロにする
			m_winnerPl->Tilt();//傾きをゼロにする
			m_winnerPl->SetArrowScele({ 0.0f,0.0f,0.0f });//矢印をゼロにする
			m_resultState = enZoomWinner;//ズームする
		}		
		else//同時に死んだとき
		{
			DeleteGO(m_gameSetFontRender);//ゲームセットフォントを消す
			//画面にDRAWと表示する
			m_winFontRender = NewGO<FontRender>(0);
			m_winFontRender->SetScale(GAMESET_FONT_SCALE);
			m_winFontRender->SetText(L"DRAW");
			m_winFontRender->SetPosition({ DRAW_FONT_POSITION });
			m_winFontRender->SetShadowFlag(true);
			m_winFontRender->SetShadowOffset(GAMESET_FONT_OFFSET);
			m_winFontRender->SetShadowColor({Vector4::Black});
			m_resultState = enDraw;//ドロー判定にする
		}

		EraseUnused();//いらないものを消す
	}
}

void ResultScene::ZoomWinner()
{
	if (m_resultBGMFlg == false)//リザルトBGMを流す
	{
		m_resultBGMFlg = true;
		m_resultBGM = NewGO<SoundSource>(0);
		m_resultBGM->Init(L"Assets/sound/リザルトBGM.wav");
		m_resultBGM->SetVolume(SOUND_RESULT_BGM_VOLUME);
		m_resultBGM->Play(true);
		g_camera3D->SetTarget({ CAMERA_TARGET_POSITION });
	}
	
	if (m_winDisplayedTime > 0)//WINが表示されている間
	{
		m_winDisplayedTime--;
		m_cameraMoveSpeed = m_cameraMoveSpeed * VALUE_MULTIPLY_IN_SPEED;//指数関数的にカメラが近寄っていく
		m_cameraPos.z += m_cameraMoveSpeed;
		
		if (m_cameraPos.z > CAMERA_SHORTEST_RANGE)//近づきすぎないようにする
		{
			m_cameraPos.z = CAMERA_SHORTEST_RANGE;//固定する
		}
		g_camera3D->SetPosition(m_cameraPos);
		return;
	}
	else if (g_pad[0]->IsTrigger(enButtonA) || m_winDisplayedTime <= 0)//Aボタンを押すか、時間が立つか
	{
		m_resultState = enMenu;//メニュー画面に移行する
		DeleteGO(m_winFontRender);//Winを消す

		m_cursorSprite = NewGO<SpriteRender>(3);//カーソルを出す
		m_cursorSprite->Init("Assets/Image/Cursor.DDS", CURSOR_SPRITE_WIDTH, CURSOR_SPRITE_HEIGHT);
		m_cursorSprite->SetPosition(RESULT_CURSOR_FONT_INI_POS);
		m_cursorSprite->SetScale({Vector3::One});

		m_retriFontRender = NewGO<FontRender>(1);
		m_retriFontRender->SetPosition(RETRI_FONT_POS);
		m_retriFontRender->SetText(L"もう一度遊ぶ。");
		m_retriFontRender->SetShadowFlag(true);
		m_retriFontRender->SetShadowColor({ 0.0f,0.0f,0.0f,1.0f });

		m_backMenuFontRender = NewGO<FontRender>(1);//メニュー
		m_backMenuFontRender->SetPosition(BACK_MENU_FONT_POS);
		m_backMenuFontRender->SetText(L"メニューへ戻る。");
		m_backMenuFontRender->SetShadowFlag(true);
		m_backMenuFontRender->SetShadowColor({ Vector4::Black });

		m_backTitleFontRender = NewGO<FontRender>(3);//タイトル
		m_backTitleFontRender->SetPosition(BACK_TITLE_FONT_POS);
		m_backTitleFontRender->SetText(L"タイトルへ戻る。");
		m_backTitleFontRender->SetShadowFlag(true);
		m_backTitleFontRender->SetShadowColor({ Vector4::Black });

	
	}
}

//タイムアップ時の処理
void ResultScene::TimeUp()
{
	if (m_timeUpDisplayedTime > 0)//タイムアップになるまで
	{
		m_timeUpDisplayedTime--;
		return;
	}
	else//タイムアップした
	{
		DeleteGO(m_gameSetFontRender);//ゲームセットフォントを消す
		//DRAWと表示する
		m_winFontRender = NewGO<FontRender>(0);
		m_winFontRender->SetScale(GAMESET_FONT_SCALE);
		m_winFontRender->SetText(L"DRAW");
		m_winFontRender->SetPosition({ 0.0f,-50.0f });
		m_winFontRender->SetShadowFlag(true);
		m_winFontRender->SetShadowOffset(GAMESET_FONT_OFFSET);
		m_winFontRender->SetShadowColor({ Vector4::Black });

		m_resultState = enDraw;//ドロー判定にする

		EraseUnused();//いらないものを消す
		//プレイヤーを探す
		QueryGOs<Player>("player", [this](Player* player)->bool {	
			player->ReturnIniPosition();//位置を設定する
			player->SetMoveSpeed(Vector3::Zero);//スピードをゼロにする
			player->Tilt();//傾きをゼロにする
			player->SetArrowScele({0.0f,0.0f,0.0f});//矢印をゼロにする

			FontRender* plFont = NewGO<FontRender>(1, "plFont");//誰が残っているか確認するためにプレイヤーの番号を表示する
			plFont->SetText(L"P" + std::to_wstring(player->GetPlayerNum() + 1));//何Pか
			plFont->SetPosition(m_plFontPos);//
			plFont->SetScale(PLAYER_FONT_SCALE);
			plFont->SetShadowFlag(true);
			plFont->SetShadowOffset(GAMESET_FONT_OFFSET);
			plFont->SetShadowColor(player->GetPlColor());

			m_plFontPos.x += 80.0f;//次のフォントのために位置をずらす
			return true;
			});

		g_camera3D->SetPosition({ -4000.0f,500.0f,0.0f });//カメラの位置を設定
	}
}

void ResultScene::Draw()//ドロー判定のとき
{
	if (m_drawDisplayedTime > 0)//ドローフォントが表示されている間
	{
		m_drawDisplayedTime--;
	}
	Vector3 right = g_camera3D->GetRight();//カメラの右方向を取得
	Vector3 cameraPos = g_camera3D->GetPosition();//カメラの位置を取得
	cameraPos += right * 40.0f;//カメラの位置をステージの中心を軸に右に回転させる
	g_camera3D->SetPosition(cameraPos);//位置を設定
		
	if (g_pad[0]->IsTrigger(enButtonA) || m_drawDisplayedTime <= 0)//Aボタンを押すか、時間が立つか
	{
		m_resultState = enMenu;//メニュー選択に移る
		DeleteGO(m_winFontRender);//ドローフォントを消す
		//生き残ったプレイヤー表示を消す
		QueryGOs<FontRender>("plFont", [this](FontRender* plFont)->bool {
			DeleteGO(plFont);
			return true;
			});
		//カーソルを表示する
		m_cursorSprite = NewGO<SpriteRender>(3);
		m_cursorSprite->Init("Assets/Image/Cursor.DDS", 64, 28);
		m_cursorSprite->SetPosition(RESULT_CURSOR_FONT_INI_POS);

		m_retriFontRender = NewGO<FontRender>(1);
		m_retriFontRender->SetPosition(RETRI_FONT_POS);
		m_retriFontRender->SetText(L"もう一度遊ぶ。");
		m_retriFontRender->SetShadowFlag(true);
		m_retriFontRender->SetShadowColor({ 0.0f,0.0f,0.0f,1.0f });
		//メニュー
		m_backMenuFontRender = NewGO<FontRender>(1);
		m_backMenuFontRender->SetPosition(BACK_MENU_FONT_POS);
		m_backMenuFontRender->SetText(L"メニューへ戻る。");
		m_backMenuFontRender->SetShadowFlag(true);
		m_backMenuFontRender->SetShadowColor({ 0.0f,0.0f,0.0f,1.0f });
		//タイトル
		m_backTitleFontRender = NewGO<FontRender>(1);
		m_backTitleFontRender->SetPosition(BACK_TITLE_FONT_POS);
		m_backTitleFontRender->SetText(L"タイトルへ戻る。");
		m_backTitleFontRender->SetShadowFlag(true);
		m_backTitleFontRender->SetShadowColor({ 0.0f,0.0f,0.0f,1.0f });

		m_lookStageFlag = true;//カメラを回すかどうか
	}
}

/// @brief メニュー表示状態
void ResultScene::Menu()
{
	SetCursorPos();//カーソルを移動させる

	if (g_pad[0]->IsTrigger(enButtonA))//Aを押せば
	{	
		m_resultSE = NewGO<SoundSource>(0);//音を出す
		m_resultSE->Init(L"Assets/sound/リザルト決定音.wav");
		m_resultSE->SetVolume(SOUND_RESULT_SE_VOLUME);
		m_resultSE->Play(false);
		if (m_selectMenu == enRetri)//リトライを押せば
		{
			//残っているプレイヤーを消す
			QueryGOs<Player>("player", [this](Player* player)->bool {
				if (player != nullptr)
					DeleteGO(player);
				return true;
				});
			
			m_gameScene->SetIniPosition();//リトライ処理::プレイヤーを作成
			m_gameScene->SetGameState(GAME_STATE_LOOK_STAGE);//ゲームシーンの状態を更新する::ステージを見渡す
			m_stageNum = m_BG->GetStageNum();//同じステージでリトライする
			m_BG->SetIniPosition();//プレイヤーの初期位置をレベルで設定する
			DeleteGO(m_BG);//バックグラウンドを作成し直す::
			BackGround* backGround = NewGO<BackGround>(0, "backGround");
			backGround->SetStageNum(m_stageNum);//同じステージを設定する
			NewGO<UIDisplay>(0, "UIdisplay");//UIを表示させる
			DeleteGO(this);//リザルトシーンを消す
		}
		else if (m_selectMenu == enBackMenu)//メニューを押せば
		{
			DeleteGO(m_gameScene);//ゲームシーンを消す			
			DeleteGO(m_BG);//バックグラウンドを消す
			//プレイヤーを消す
			QueryGOs<Player>("player", [this](Player* player)->bool {
				DeleteGO(player);
				return true;
				});
			DeleteGO(this);//リザルトシーンを消す
			NewGO<TitleBack>(0, "titleBack");//タイトル背景を作成する
			NewGO<SelectScene>(0, "selectScene");//選択画面を作成する
		}
		else if (m_selectMenu == enBackTitle)//タイトルを押せば
		{
			DeleteGO(m_gameScene);//ゲームシーンを消す			
			DeleteGO(m_BG);//バックグラウンドを消す
			//プレイヤーを消す
			QueryGOs<Player>("player", [this](Player* player)->bool {
				DeleteGO(player);
				return true;
				});
			DeleteGO(this);//リザルトシーンを消す
			NewGO<TitleBack>(0, "titleBack");//タイトル背景を作成する
			NewGO<TitleScene>(0, "titleScene");//タイトルを作成する
		}
	}
	
	if (m_lookStageFlag == true)
	{//ステージの中心を軸にカメラを回転させる
		Vector3 right = g_camera3D->GetRight();
		Vector3 cameraPos = g_camera3D->GetPosition();
		cameraPos += right * 40.0f;
		g_camera3D->SetPosition(cameraPos);
	}
}
//カーソルの位置を決める。
void ResultScene::SetCursorPos()
{
	if (g_pad[0]->IsTrigger(enButtonDown))//下ボタンを押せば
	{
		//音を出す
		m_resultSE = NewGO<SoundSource>(0);
		m_resultSE->Init(L"Assets/sound/リザルト選択音.wav");
		m_resultSE->SetVolume(SOUND_RESULT_SE_VOLUME);
		m_resultSE->Play(false);

		isSelectMenu(false);
	}
	else if (g_pad[0]->IsTrigger(enButtonUp))//上ボタンを押せば
	{
		//音を出す
		m_resultSE = NewGO<SoundSource>(0);
		m_resultSE->Init(L"Assets/sound/リザルト選択音.wav");
		m_resultSE->SetVolume(SOUND_RESULT_SE_VOLUME);
		m_resultSE->Play(false);

		isSelectMenu(true);
	}

	//カーソルの左右の動き
	m_cursorMoveSpeedX += 0.1;
	m_cursorPos.x += pow(m_cursorMoveSpeedX,0.5f) ;
	
	if (m_cursorPos.x > CURSOR_FONT_MAX_POS_X)	//カーソルの動きをリセットする。
	{
		m_cursorMoveSpeedX = INI_CURSOR_MOVE_SPEED_X;
		m_cursorPos.x = RESULT_CURSOR_FONT_INI_POS.x;
	}
	m_cursorSprite->SetPosition(m_cursorPos);
}

//カーソルの位置を上下に移動する。
void ResultScene::isSelectMenu(bool isUp)
{
	if (isUp == true)
	{
		if (m_selectMenu == enRetri)
		{
			m_selectMenu = enBackTitle;
		}
		else if (m_selectMenu == enBackMenu)
		{
			m_selectMenu = enRetri;
		}
		else if(m_selectMenu == enBackTitle)
		{
			m_selectMenu = enBackMenu;
		}
	}
	else if (isUp == false)
	{
		if (m_selectMenu == enRetri)
		{
			m_selectMenu = enBackMenu;
		}
		else if (m_selectMenu == enBackMenu)
		{
			m_selectMenu = enBackTitle;
		}
		else if(m_selectMenu == enBackTitle)
		{
			m_selectMenu = enRetri;
		}
	}
	
	switch (m_selectMenu)
	{
	case enRetri:
		m_cursorPos.y = RETRI_FONT_POS.y - 20;
		break;
	case enBackMenu:
		m_cursorPos.y = BACK_MENU_FONT_POS.y - 20;
		break;
	case enBackTitle:
		m_cursorPos.y = BACK_TITLE_FONT_POS.y - 20;
		break;
	}
}

void ResultScene::EraseUnused()
{
	//風船UIを消す
	QueryGOs<UIDisplay>("UIdisplay", [this](UIDisplay* UIdisplay)->bool {
		DeleteGO(UIdisplay);
		return true;
		});
	//風車を消す
	QueryGOs<WindTurbine>("windTurbine", [this](WindTurbine* windTurbine)->bool {
		DeleteGO(windTurbine);
		return true;
		});
	//棘を消す
	QueryGOs<GimmickNeedle>("gimmickNeedle", [this](GimmickNeedle* gimmickNeedle)->bool {
		DeleteGO(gimmickNeedle);
		return true;
		});
	//タイム表示を消す
	QueryGOs<GameTimer>("gameTimer", [this](GameTimer* gameTimer)->bool {
		DeleteGO(gameTimer);
		return true;
		});
}