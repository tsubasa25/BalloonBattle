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

ResultScene::~ResultScene()
{
	if (m_selectMenuNum == 0)
	{
		BackGround* backGround = NewGO<BackGround>(0, "backGround");
		backGround->SetStageNum(m_stageNum);
	}
	//DeleteGO(m_retriFontRender);
	DeleteGO(m_backMenuFontRender);
	DeleteGO(m_backTitleFontRender);
	DeleteGO(m_cursorSprite);
	DeleteGO(m_resultBGM);
}

bool ResultScene::Start()
{
	m_BG = FindGO<BackGround>("backGround");
	m_gameScene = FindGO<GameScene>("gameScene");

	m_gameSetFontRender = NewGO<FontRender>(0);
	m_gameSetFontRender->SetPosition({-200.0f,0.0f});
	m_gameSetFontRender->SetScale(2.0f);
	m_gameSetFontRender->SetShadowFlag(true);
	m_gameSetFontRender->SetShadowOffset(3.0f);
	m_gameSetFontRender->SetShadowColor({ 0.0f,0.0f,0.0f,1.0f });

	if (m_mode == MODE_GAME_SET)
		m_gameSetFontRender->SetText(L"GAME SET");
	else if (m_mode == MODE_TIME_UP)
		m_gameSetFontRender->SetText(L"TIME  UP");
	else 
		m_gameSetFontRender->SetText(L"H O  G E");

	QueryGOs<BalloonAir>("balloonAir", [this](BalloonAir* balloonAir)->bool {
		DeleteGO(balloonAir);
		return true;
		});


	//m_mode = MODE_GAME_SET;

	return true;
}
void ResultScene::Update()
{
	switch (m_mode)
	{
	case MODE_GAME_SET:
		GameSet();
		break;
		
	case MODE_ZOOM_WINNER:
		ZoomWinner();
		break;
	case MODE_TIME_UP:
		TimeUp();
		break;
	case MODE_DRAW:
		Draw();
		break;
	case MODE_MENU:
		Menu();
		break;
	}
}

//ゲームに決着がついた時の処理
void ResultScene::GameSet()
{
	if (m_gameSetFontTimer > 0)
	{
		m_gameSetFontTimer--;
		return;
	}
	else
	{
		if (m_winnerPl != nullptr)
		{
			m_mode = MODE_ZOOM_WINNER;
			DeleteGO(m_gameSetFontRender);
			m_winFontRender = NewGO<FontRender>(0);
			m_winFontRender->SetScale(2.0f);
			m_winFontRender->SetText(L"PLAYER " + std::to_wstring(m_winnerPl->GetPlayerNum() + 1) + L" WIN!!");
			m_winFontRender->SetPosition({ -300.0f,0.0f });
			m_winFontRender->SetShadowFlag(true);
			m_winFontRender->SetShadowOffset(3.0f);
			m_winFontRender->SetShadowColor({ m_winnerPl->GetPlColor() });

			m_winnerPl->SetPosition(m_winnerPos);
			m_winnerPl->SetMoveSpeed(Vector3::Zero);
			m_winnerPl->Tilt();
			m_winnerPl->SetArrowScele({ 0.0f,0.0f,0.0f });
		}
		//ドローの時
		else
		{
			m_mode = MODE_DRAW;
			DeleteGO(m_gameSetFontRender);
			m_winFontRender = NewGO<FontRender>(0);
			m_winFontRender->SetScale(2.0f);
			m_winFontRender->SetText(L"DRAW");
			m_winFontRender->SetPosition({ -70.0f,0.0f });
			m_winFontRender->SetShadowFlag(true);
			m_winFontRender->SetShadowOffset(3.0f);
			m_winFontRender->SetShadowColor({Vector4::Black});
		}

		QueryGOs<UIDisplay>("UIdisplay", [this](UIDisplay* UIdisplay)->bool {
			DeleteGO(UIdisplay);
			return true;
			});
		QueryGOs<WindTurbine>("windTurbine", [this](WindTurbine* windTurbine)->bool {
			DeleteGO(windTurbine);
			return true;
			});
		QueryGOs<GimmickNeedle>("gimmickNeedle", [this](GimmickNeedle* gimmickNeedle)->bool {
			DeleteGO(gimmickNeedle);
			return true;
			});
		QueryGOs<GameTimer>("gameTimer", [this](GameTimer* gameTimer)->bool {
			DeleteGO(gameTimer);
			return true;
			});
		QueryGOs<SoundSource>("mapBGM", [this](SoundSource* mapBGM)->bool {
			DeleteGO(mapBGM);
			return true;
			});

		g_camera3D->SetPosition(m_cameraPos);
		g_camera3D->SetTarget({0.0f,100.0f, 0.0f});

	}
}

void ResultScene::ZoomWinner()
{
	if (m_resultBGMFlg == false)
	{
		m_resultBGMFlg = true;
		m_resultBGM = NewGO<SoundSource>(0);
		m_resultBGM->Init(L"Assets/sound/リザルトBGM.wav");
		m_resultBGM->SetVolume(SOUND_RESULT_BGM_VOLUME);
		m_resultBGM->Play(true);
	}
	
	if (m_winFontTimer > 0)
	{
		m_winFontTimer--;
		m_cameraMoveSpeed = m_cameraMoveSpeed * 1.05f;
		m_cameraPos.z += m_cameraMoveSpeed;
		
		if (m_cameraPos.z > -500.0f)
		{
			m_cameraPos.z = -500.0f;
		}
		g_camera3D->SetPosition(m_cameraPos);
		return;
	}
	else if (g_pad[0]->IsTrigger(enButtonA) || m_winFontTimer <= 0)
	{
		m_mode = MODE_MENU;
		DeleteGO(m_winFontRender);

		m_cursorSprite = NewGO<SpriteRender>(3);
		m_cursorSprite->Init("Assets/Image/Cursor.DDS", 64, 28);
		m_cursorSprite->SetPosition(RESULT_CURSOR_FONT_INI_POS);
		m_cursorSprite->SetScale({1.0f,1.0f,1.0f});

		/*m_retriFontRender = NewGO<FontRender>(1);
		m_retriFontRender->SetPosition(RETRI_FONT_POS);
		m_retriFontRender->SetText(L"もう一度遊ぶ。");
		m_retriFontRender->SetShadowFlag(true);
		m_retriFontRender->SetShadowColor({ 0.0f,0.0f,0.0f,1.0f });*/

		m_backMenuFontRender = NewGO<FontRender>(1);
		m_backMenuFontRender->SetPosition(BACK_MENU_FONT_POS);
		m_backMenuFontRender->SetText(L"メニューへ戻る。");
		m_backMenuFontRender->SetShadowFlag(true);
		m_backMenuFontRender->SetShadowColor({ 0.0f,0.0f,0.0f,1.0f });

		m_backTitleFontRender = NewGO<FontRender>(3);
		m_backTitleFontRender->SetPosition(BACK_TITLE_FONT_POS);
		m_backTitleFontRender->SetText(L"タイトルへ戻る。");
		m_backTitleFontRender->SetShadowFlag(true);
		m_backTitleFontRender->SetShadowColor({ 0.0f,0.0f,0.0f,1.0f });

	
	}
}

//タイムアップ時の処理
void ResultScene::TimeUp()
{
	if (m_gameSetFontTimer > 0)
	{
		m_gameSetFontTimer--;
		return;
	}
	else
	{
		m_mode = MODE_DRAW;
		DeleteGO(m_gameSetFontRender);
		m_winFontRender = NewGO<FontRender>(0);
		m_winFontRender->SetScale(2.5f);
		m_winFontRender->SetText(L"DRAW");
		m_winFontRender->SetPosition({ 0.0f,-50.0f });
		m_winFontRender->SetShadowFlag(true);
		m_winFontRender->SetShadowOffset(4.0f);
		m_winFontRender->SetShadowColor({ 0.0f,0.0f,0.0f,1.0f });

		QueryGOs<UIDisplay>("UIdisplay", [this](UIDisplay* UIdisplay)->bool {
			DeleteGO(UIdisplay);
			return true;
			});
		QueryGOs<WindTurbine>("windTurbine", [this](WindTurbine* windTurbine)->bool {
			DeleteGO(windTurbine);
			return true;
			});
		QueryGOs<GimmickNeedle>("gimmickNeedle", [this](GimmickNeedle* gimmickNeedle)->bool {
			DeleteGO(gimmickNeedle);
			return true;
			});
		QueryGOs<GameTimer>("gameTimer", [this](GameTimer* gameTimer)->bool {
			DeleteGO(gameTimer);
			return true;
			});

		QueryGOs<Player>("player", [this](Player* player)->bool {	
			player->ReturnIniPosition();
			player->SetMoveSpeed(Vector3::Zero);
			player->Tilt();
			player->SetArrowScele({0.0f,0.0f,0.0f});

			FontRender* plFont = NewGO<FontRender>(1, "plFont");
			plFont->SetText(L"P" + std::to_wstring(player->GetPlayerNum() + 1));
			plFont->SetPosition(plFontPos);
			plFont->SetScale(1.5f);
			plFont->SetShadowFlag(true);
			plFont->SetShadowOffset(3.0f);
			plFont->SetShadowColor(player->GetPlColor());

			plFontPos.x += 80.0f;
			return true;
			});

		g_camera3D->SetPosition({ -4000.0f,500.0f,0.0f });
	}
}

void ResultScene::Draw()
{
	if (m_winFontTimer > 0)
	{
		m_winFontTimer--;
	}
	Vector3 right = g_camera3D->GetRight();
	Vector3 cameraPos = g_camera3D->GetPosition();
	cameraPos += right * 40.0f;
	g_camera3D->SetPosition(cameraPos);
		
	if (g_pad[0]->IsTrigger(enButtonA) || m_winFontTimer <= 0)
	{
		m_mode = MODE_MENU;
		DeleteGO(m_winFontRender);

		QueryGOs<FontRender>("plFont", [this](FontRender* plFont)->bool {
			DeleteGO(plFont);
			return true;
			});

		m_cursorSprite = NewGO<SpriteRender>(3);
		m_cursorSprite->Init("Assets/Image/Cursor.DDS", 64, 28);
		m_cursorSprite->SetPosition(RESULT_CURSOR_FONT_INI_POS);

		/*m_retriFontRender = NewGO<FontRender>(1);
		m_retriFontRender->SetPosition(RETRI_FONT_POS);
		m_retriFontRender->SetText(L"もう一度遊ぶ。");
		m_retriFontRender->SetShadowFlag(true);
		m_retriFontRender->SetShadowColor({ 0.0f,0.0f,0.0f,1.0f });*/

		m_backMenuFontRender = NewGO<FontRender>(1);
		m_backMenuFontRender->SetPosition(BACK_MENU_FONT_POS);
		m_backMenuFontRender->SetText(L"メニューへ戻る。");
		m_backMenuFontRender->SetShadowFlag(true);
		m_backMenuFontRender->SetShadowColor({ 0.0f,0.0f,0.0f,1.0f });

		m_backTitleFontRender = NewGO<FontRender>(1);
		m_backTitleFontRender->SetPosition(BACK_TITLE_FONT_POS);
		m_backTitleFontRender->SetText(L"タイトルへ戻る。");
		m_backTitleFontRender->SetShadowFlag(true);
		m_backTitleFontRender->SetShadowColor({ 0.0f,0.0f,0.0f,1.0f });

		m_lookStageFlag = true;
	}
}

void ResultScene::Menu()
{
	SetCursorPos();

	if (g_pad[0]->IsTrigger(enButtonA))
	{	
		m_resultSE = NewGO<SoundSource>(0);
		m_resultSE->Init(L"Assets/sound/リザルト決定音.wav");
		m_resultSE->SetVolume(SOUND_RESULT_SE_VOLUME);
		m_resultSE->Play(false);
		if (m_selectMenuNum == 0)
		{			
			m_gameScene->Retri();
			m_gameScene->SetGameState(GAME_STATE_LOOK_STAGE);
			m_gameScene->PlayerDelete();
			m_stageNum = m_BG->GetStageNum();
			//m_BG->Retri();
			DeleteGO(m_BG);
				
			/*QueryGOs<Player>("player", [this](Player* player)->bool {
				if (player != nullptr)
					DeleteGO(player);
				return true;
				});*/

			
			NewGO<UIDisplay>(0, "UIdisplay");
			DeleteGO(this);
		}
		else if (m_selectMenuNum == 1)
		{
			DeleteGO(m_gameScene);
			
			DeleteGO(m_BG);
				
			QueryGOs<Player>("player", [this](Player* player)->bool {
				DeleteGO(player);
				return true;
				});
			DeleteGO(this);
			NewGO<TitleBack>(0, "titleBack");
			NewGO<SelectScene>(0, "selectScene");
		}
		else if (m_selectMenuNum == 2)
		{
			DeleteGO(m_gameScene);

			DeleteGO(m_BG);
				
			QueryGOs<Player>("player", [this](Player* player)->bool {
				DeleteGO(player);
				return true;
				});
			DeleteGO(this);
			NewGO<TitleBack>(0, "titleBack");
			NewGO<TitleScene>(0, "titleScene");
		}
	}

	if (m_lookStageFlag == true)
	{
		Vector3 right = g_camera3D->GetRight();
		Vector3 cameraPos = g_camera3D->GetPosition();
		cameraPos += right * 40.0f;
		g_camera3D->SetPosition(cameraPos);
	}
}
//カーソルの位置を決める。
void ResultScene::SetCursorPos()
{
	if (g_pad[0]->IsTrigger(enButtonDown))
	{
		m_resultSE = NewGO<SoundSource>(0);
		m_resultSE->Init(L"Assets/sound/リザルト選択音.wav");
		m_resultSE->SetVolume(SOUND_RESULT_SE_VOLUME);
		m_resultSE->Play(false);

		AddSelectMenuNum(1);
	}
	else if (g_pad[0]->IsTrigger(enButtonUp))
	{
		m_resultSE = NewGO<SoundSource>(0);
		m_resultSE->Init(L"Assets/sound/リザルト選択音.wav");
		m_resultSE->SetVolume(SOUND_RESULT_SE_VOLUME);
		m_resultSE->Play(false);

		AddSelectMenuNum(-1);
	}

	//カーソルの左右の動き
	m_cursorMoveSpeedX -= 0.1f;

	if(m_cursorMoveSpeedX > 0)
		m_cursorPos.x -= m_cursorMoveSpeedX * m_cursorMoveSpeedX;
	else 
		m_cursorPos.x += m_cursorMoveSpeedX * m_cursorMoveSpeedX;

	if (m_cursorPos.x > RESULT_CURSOR_FONT_INI_POS.x)	//カーソルの動きをリセットする。
	{
		m_cursorMoveSpeedX = INI_CURSOR_MOVE_SPEED_X;
		m_cursorPos.x = RESULT_CURSOR_FONT_INI_POS.x;
	}
	m_cursorSprite->SetPosition(m_cursorPos);
}

//カーソルの位置を上下に移動する。
void ResultScene::AddSelectMenuNum(int num)
{
	m_selectMenuNum += num;
	//0～2までしか選択できない。
	if (m_selectMenuNum > 2)
		m_selectMenuNum = 1;
	else if (m_selectMenuNum < 1)
		m_selectMenuNum = 2;

	switch (m_selectMenuNum)
	{
	case 0:
		m_cursorPos.y = RETRI_FONT_POS.y - 20;
		break;
	case 1:
		m_cursorPos.y = BACK_MENU_FONT_POS.y - 20;
		break;
	case 2:
		m_cursorPos.y = BACK_TITLE_FONT_POS.y - 20;
		break;
	}
}