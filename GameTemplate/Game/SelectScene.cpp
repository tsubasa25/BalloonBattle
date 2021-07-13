#include "stdafx.h"
#include "SelectScene.h"
#include "BackGround.h"
#include "GameScene.h"
#include "TitleBack.h"
#include "UIDisplay.h"
#include "TitleScene.h"

SelectScene::~SelectScene()
{
	DeleteGO(m_cPlayer_Sprite);
	DeleteGO(m_cStock_Sprite);
	DeleteGO(m_cPlayerCount_Sprite);
	DeleteGO(m_cStockNum_Sprite);
	DeleteGO(m_arrowPlayer_Sprite);
	DeleteGO(m_arrowStock_Sprite);
	DeleteGO(m_cPlayer_Sprite);
	DeleteGO(m_cStock_Sprite);
	DeleteGO(m_cStage_Sprite);
	
	
	for (int i = 0; i < 8; i++)
	{
		DeleteGO(m_playerUI_Sprite[i]);
		DeleteGO(m_stageBalloon_Sprite[i/2]);
	}	
	if (m_okPlayer_Sprite != nullptr)
		DeleteGO(m_okPlayer_Sprite);
	if (m_okStok_Sprite != nullptr)
		DeleteGO(m_okStok_Sprite);
	if (m_titleBackFont != nullptr)
		DeleteGO(m_titleBackFont);
	if (m_selectBGM != nullptr)
		DeleteGO(m_selectBGM);
}

bool SelectScene::Start()
{
	m_cPlayer_Sprite = NewGO<SpriteRender>(0);
	m_cPlayer_Sprite->Init("Assets/Image/cPlayer.dds", 500, 160);
	m_cPlayer_Sprite->SetPosition(m_cPlayerPos);
	m_cStock_Sprite = NewGO<SpriteRender>(0);
	m_cStock_Sprite->Init("Assets/Image/cStock.dds", 500, 160);
	m_cStock_Sprite->SetPosition(m_cStockPos);
	m_cStage_Sprite = NewGO<SpriteRender>(0);
	m_cStage_Sprite->Init("Assets/Image/cStage.dds", 500, 160);
	m_cStage_Sprite->SetPosition(m_StagePos);

	m_cPlayerCount_Sprite=NewGO<SpriteRender>(0);
	m_cPlayerCount_Sprite->Init("Assets/Image/c2.dds", 70, 140);
	m_cPlayerCount_Sprite->SetPosition(m_cPlayerNumPos);
	m_cStockNum_Sprite = NewGO<SpriteRender>(0);
	m_cStockNum_Sprite->Init("Assets/Image/c3.dds", 70, 140);
	m_cStockNum_Sprite->SetPosition(m_cStockNumPos);

	m_arrowPlayer_Sprite=NewGO<SpriteRender>(0);
	m_arrowPlayer_Sprite->Init("Assets/Image/selectArrowOK.dds", 100, 200);
	m_arrowPlayer_Sprite->SetPosition(m_arrowPlayerPos);
	m_arrowStock_Sprite=NewGO<SpriteRender>(0);
	m_arrowStock_Sprite->Init("Assets/Image/selectArrowOK.dds", 100, 200);
	m_arrowStock_Sprite->SetPosition(m_arrowStockPos);

	for (int i = 0; i<4;i++)
	{
		m_stageBalloon_Sprite[i] = NewGO<SpriteRender>(0);
	}
	m_stageBalloon_Sprite[0]->Init("Assets/Image/stageBalloon0.dds", 186, 256);
	m_stageBalloon_Sprite[1]->Init("Assets/Image/stageBalloon1.dds", 186, 256);
	m_stageBalloon_Sprite[2]->Init("Assets/Image/stageBalloon2.dds", 186, 256);
	m_stageBalloon_Sprite[3]->Init("Assets/Image/stageBalloon3.dds", 186, 256);
	for (int i = 0; i < 4; i++)
	{
		m_stageBalloon_Sprite[i]->SetPosition(m_stageBalloonPos[i]);
	}

	for (int i = 0; i < 8; i++)
	{
		m_playerUI_Sprite[i] = NewGO<SpriteRender>(0);
	}
	m_playerUI_Sprite[0]->Init("Assets/Image/ballooooooon.red.dds",    126,210);
	m_playerUI_Sprite[1]->Init("Assets/Image/ballooooooon.blue.dds",   126,210);
	m_playerUI_Sprite[2]->Init("Assets/Image/ballooooooon.green.dds",  126,210);
	m_playerUI_Sprite[3]->Init("Assets/Image/ballooooooon.yellow.dds", 126,210);
	m_playerUI_Sprite[4]->Init("Assets/Image/ballooooooon.orange.dds", 126,210);
	m_playerUI_Sprite[5]->Init("Assets/Image/ballooooooon.pink.dds",   126,210);
	m_playerUI_Sprite[6]->Init("Assets/Image/ballooooooon.gray.dds",   126,210);
	m_playerUI_Sprite[7]->Init("Assets/Image/ballooooooon.purple.dds", 126,210);
	for (int i = 0; i < 8; i++)
	{
		m_playerUI_Sprite[i]->SetPosition(m_playerUIPos[i]);
		m_playerUI_Sprite[i]->SetScale(Vector3::Zero);
	}
	m_playerUI_Sprite[0]->SetScale(Vector3::One);
	m_playerUI_Sprite[1]->SetScale(Vector3::One);

	m_selectBGM = NewGO<SoundSource>(0);
	m_selectBGM->Init(L"Assets/sound/マップ選択画面BGM.wav", SoundType::enBGM);
	m_selectBGM->SetVolume(SOUND_SELECT_BGM_VOLUME);
	m_selectBGM->Play(true);

	return true;
}

void SelectScene::Update()
{
	if ((m_titleState == TitleState::enBackTitle))
	{
		if (g_pad[0]->IsTrigger(enButtonB))
		{
			m_titleState = enPlayerNum;
			DeleteGO(m_titleBackFont);
		}
		else if (g_pad[0]->IsTrigger(enButtonA))
		{
			DeleteGO(this);
			NewGO<TitleScene>(0,"titleScene");
		}
	}
	else if (m_titleState == TitleState::enPlayerNum)
	{
		if (g_pad[0]->IsTrigger(enButtonB))
		{
			m_titleState = enBackTitle;
			m_titleBackFont = NewGO<FontRender>(1);
			m_titleBackFont->SetPosition({ -350.0f, 30.0f });
			m_titleBackFont->SetScale(1.5f);
			m_titleBackFont->SetShadowFlag(true);
			m_titleBackFont->SetShadowColor({ Vector4::Black });
			m_titleBackFont->SetText
			(L"タイトルへ戻りますか？\n"
				L"　A はい　　B いいえ");
		}
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			m_okPlayer_Sprite = NewGO<SpriteRender>(0);
			m_okPlayer_Sprite->Init("Assets/Image/OK!.dds", 240, 135);
			m_okPlayer_Sprite->SetPosition(m_okPlayerPos);
			m_titleState = enPlayerStock;
			m_arrowLoopCount = 0;
			m_arrowPlayer_Sprite->Init("Assets/Image/selectArrowOK.dds", 100, 200);
			m_selectSE = NewGO<SoundSource>(0);
			m_selectSE->Init(L"Assets/sound/セレクト決定音.wav");
			m_selectSE->SetVolume(SOUND_SELECT_SE_VOLUME);
			m_selectSE->Play(false);
		}
		if (g_pad[0]->IsTrigger(enButtonUp))
		{
			m_playerCount++;//人数を増やす
			if (m_playerCount > 8)
			{
				m_playerCount = 2;
				m_selectSE = NewGO<SoundSource>(0);
				m_selectSE->Init(L"Assets/sound/選択音.wav");
				m_selectSE->SetVolume(SOUND_SELECT_SE_VOLUME);
				m_selectSE->Play(false);
			}
		}
		if (g_pad[0]->IsTrigger(enButtonDown))
		{
			m_playerCount--;//人数を減らす
			if (m_playerCount < 2)
			{
				m_playerCount = 8;
				m_selectSE = NewGO<SoundSource>(0);
				m_selectSE->Init(L"Assets/sound/選択音.wav");
				m_selectSE->SetVolume(SOUND_SELECT_SE_VOLUME);
				m_selectSE->Play(false);
			}
		}
		if (g_pad[0]->IsTrigger(enButtonUp) || g_pad[0]->IsTrigger(enButtonDown))
		{
			switch (m_playerCount)
			{
			case 2:
				m_cPlayerCount_Sprite->Init("Assets/Image/c2.dds", 70, 140);
				for (int i = 0; i < m_playerCount; i++)
				{
					m_playerUI_Sprite[i]->SetScale({ Vector3::One });
				}
				for (int i = 7; i >= m_playerCount; i--)
				{
					m_playerUI_Sprite[i]->SetScale({ Vector3::Zero });
				}
				break;
			case 3:
				m_cPlayerCount_Sprite->Init("Assets/Image/c3.dds", 70, 140);
				for (int i = 0; i < m_playerCount; i++)
				{
					m_playerUI_Sprite[i]->SetScale({ Vector3::One });
				}
				for (int i = 7; i >= m_playerCount; i--)
				{
					m_playerUI_Sprite[i]->SetScale({ Vector3::Zero });
				}
				break;
			case 4:
				m_cPlayerCount_Sprite->Init("Assets/Image/c4.dds", 70, 140);
				for (int i = 0; i < m_playerCount; i++)
				{
					m_playerUI_Sprite[i]->SetScale({ Vector3::One });
				}
				for (int i = 7; i >= m_playerCount; i--)
				{
					m_playerUI_Sprite[i]->SetScale({ Vector3::Zero });
				}
				break;
			case 5:
				m_cPlayerCount_Sprite->Init("Assets/Image/c5.dds", 70, 140);
				for (int i = 0; i < m_playerCount; i++)
				{
					m_playerUI_Sprite[i]->SetScale({ Vector3::One });
				}
				for (int i = 7; i >= m_playerCount; i--)
				{
					m_playerUI_Sprite[i]->SetScale({ Vector3::Zero });
				}
				break;
			case 6:
				m_cPlayerCount_Sprite->Init("Assets/Image/c6.dds", 70, 140);
				for (int i = 0; i < m_playerCount; i++)
				{
					m_playerUI_Sprite[i]->SetScale({ Vector3::One });
				}
				for (int i = 7; i >= m_playerCount; i--)
				{
					m_playerUI_Sprite[i]->SetScale({ Vector3::Zero });
				}
				break;
			case 7:
				m_cPlayerCount_Sprite->Init("Assets/Image/c7.dds", 70, 140);
				for (int i = 0; i < m_playerCount; i++)
				{
					m_playerUI_Sprite[i]->SetScale({ Vector3::One });
				}
				for (int i = 7; i >= m_playerCount; i--)
				{
					m_playerUI_Sprite[i]->SetScale({ Vector3::Zero });
				}
				break;
			case 8:
				m_cPlayerCount_Sprite->Init("Assets/Image/c8.dds", 70, 140);
				for (int i = 0; i < m_playerCount; i++)
				{
					m_playerUI_Sprite[i]->SetScale({ Vector3::One });
				}
				break;
			default:
				break;
			}
			m_selectSE = NewGO<SoundSource>(0);
			m_selectSE->Init(L"Assets/sound/選択音.wav");
			m_selectSE->SetVolume(SOUND_SELECT_SE_VOLUME);
			m_selectSE->Play(false);
		}
		m_arrowLoopCount++;
		if (m_arrowLoopCount % m_arrowSwichTime == 0)
		{
			if (m_arrowFlag == true)
				m_arrowFlag = false;
			else
				m_arrowFlag = true;
			if(m_arrowFlag==true)
				m_arrowPlayer_Sprite->Init("Assets/Image/selectArrow.dds", 100, 200);
			else
				m_arrowPlayer_Sprite->Init("Assets/Image/selectArrowOK.dds", 100, 200);
		}
		
	}
	else if (m_titleState == enPlayerStock)
	{
		if (g_pad[0]->IsTrigger(enButtonB))
		{
			m_titleState = enPlayerNum;
			DeleteGO(m_okPlayer_Sprite);
		}
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			m_okStok_Sprite = NewGO<SpriteRender>(0);
			m_okStok_Sprite->Init("Assets/Image/OK!.dds", 240, 135);
			m_okStok_Sprite->SetPosition(m_okStockPos);
			m_titleState = enStageSelect;
			m_arrowPlayer_Sprite->Init("Assets/Image/selectArrowOK.dds", 100, 200);
			m_selectSE = NewGO<SoundSource>(0);
			m_selectSE->Init(L"Assets/sound/セレクト決定音.wav");
			m_selectSE->SetVolume(SOUND_SELECT_SE_VOLUME);
			m_selectSE->Play(false);
		}
		if (g_pad[0]->IsTrigger(enButtonUp))
		{
			m_playerStock++;//人数を増やす
			if (m_playerStock > 9)
			{
				m_playerStock = 1;
			}
			m_selectSE = NewGO<SoundSource>(0);
			m_selectSE->Init(L"Assets/sound/選択音.wav");
			m_selectSE->SetVolume(SOUND_SELECT_SE_VOLUME);
			m_selectSE->Play(false);
		}
		if (g_pad[0]->IsTrigger(enButtonDown))
		{

			m_playerStock--;//人数を減らす
			if (m_playerStock < 1)
			{
				m_playerStock = 9;
			}
			m_selectSE = NewGO<SoundSource>(0);
			m_selectSE->Init(L"Assets/sound/選択音.wav");
			m_selectSE->SetVolume(SOUND_SELECT_SE_VOLUME);
			m_selectSE->Play(false);
		}
		if (g_pad[0]->IsTrigger(enButtonUp) || g_pad[0]->IsTrigger(enButtonDown))
		{
			
			switch (m_playerStock)
			{
			case 0:
				m_cStockNum_Sprite->Init("Assets/Image/c0.dds", 70, 140);
				break;
			case 1:
				m_cStockNum_Sprite->Init("Assets/Image/c1.dds", 70, 140);
				break;
			case 2:
				m_cStockNum_Sprite->Init("Assets/Image/c2.dds", 70, 140);
				break;
			case 3:
				m_cStockNum_Sprite->Init("Assets/Image/c3.dds", 70, 140);
				break;
			case 4:
				m_cStockNum_Sprite->Init("Assets/Image/c4.dds", 70, 140);
				break;
			case 5:
				m_cStockNum_Sprite->Init("Assets/Image/c5.dds", 70, 140);
				break;
			case 6:
				m_cStockNum_Sprite->Init("Assets/Image/c6.dds", 70, 140);
				break;
			case 7:
				m_cStockNum_Sprite->Init("Assets/Image/c7.dds", 70, 140);
				break;
			case 8:
				m_cStockNum_Sprite->Init("Assets/Image/c8.dds", 70, 140);
				break;
			case 9:
				m_cStockNum_Sprite->Init("Assets/Image/c9.dds", 70, 140);
				break;
			default:
				break;
			}					
		}
		m_arrowLoopCount++;
		if (m_arrowLoopCount % m_arrowSwichTime == 0)
		{
			if (m_arrowFlag == true) {
				m_arrowFlag = false;
			}
			else {
				m_arrowFlag = true;
			}
			if (m_arrowFlag == true) {
				m_arrowStock_Sprite->Init("Assets/Image/selectArrow.dds", 100, 200);
			}
			else {
				m_arrowStock_Sprite->Init("Assets/Image/selectArrowOK.dds", 100, 200);
			}
		}
	}
	else if (m_titleState==enStageSelect)
	{
		if (g_pad[0]->IsTrigger(enButtonB))
		{
			m_titleState = enPlayerStock;
			DeleteGO(m_okStok_Sprite);
		}
		if (g_pad[0]->IsTrigger(enButtonA))
		{	
			m_selectSE = NewGO<SoundSource>(0);
			m_selectSE->Init(L"Assets/sound/セレクト決定音.wav");
			m_selectSE->SetVolume(SOUND_SELECT_SE_VOLUME);
			m_selectSE->Play(false);
			DeleteGO(m_selectBGM);
			GameScene* gameScene = NewGO<GameScene>(0, "gameScene");
			gameScene->SetPlayerCount(m_playerCount);
			gameScene->SetStock(m_playerStock);
			BackGround* backGround = NewGO<BackGround>(0, "backGround");
			backGround->SetStageNum(m_stageNum);
			NewGO<UIDisplay>(0, "UIdisplay");//= UIDisplay* UIdisplay 
			TitleBack*titleBack = FindGO<TitleBack>("titleBack");
			titleBack->SetDestroy(true);
			DeleteGO(this);
		}
		if (g_pad[0]->IsTrigger(enButtonUp))
		{
			m_selectSE = NewGO<SoundSource>(0);
			m_selectSE->Init(L"Assets/sound/選択音.wav");
			m_selectSE->SetVolume(SOUND_SELECT_SE_VOLUME);
			m_selectSE->Play(false);
			m_XNum++;
			m_selectLoopCount = 0;
			if (m_XNum > 1)
			{
				m_XNum = 0;
			}
		}
		if (g_pad[0]->IsTrigger(enButtonDown))
		{
			m_selectSE = NewGO<SoundSource>(0);
			m_selectSE->Init(L"Assets/sound/選択音.wav");
			m_selectSE->SetVolume(SOUND_SELECT_SE_VOLUME);
			m_selectSE->Play(false);
			m_XNum--;
			m_selectLoopCount = 0;
			if (m_XNum < 0)
			{
				m_XNum = 1;
			}
		}
		if (g_pad[0]->IsTrigger(enButtonRight))
		{
			m_selectSE = NewGO<SoundSource>(0);
			m_selectSE->Init(L"Assets/sound/選択音.wav");
			m_selectSE->SetVolume(SOUND_SELECT_SE_VOLUME);
			m_selectSE->Play(false);
			m_YNum++;
			m_selectLoopCount = 0;
			if (m_YNum > 1)
			{
				m_YNum = 0;
			}
		}
		if (g_pad[0]->IsTrigger(enButtonLeft))
		{
			m_selectSE = NewGO<SoundSource>(0);
			m_selectSE->Init(L"Assets/sound/選択音.wav");
			m_selectSE->SetVolume(SOUND_SELECT_SE_VOLUME);
			m_selectSE->Play(false);
			m_YNum--;
			m_selectLoopCount = 0;
			if (m_YNum < 0)
			{
				m_YNum = 1;
			}
		}
		m_selectNum[0][0] = false;
		m_selectNum[0][1] = false;
		m_selectNum[1][0] = false;
		m_selectNum[1][1] = false;
		m_selectNum[m_XNum][m_YNum] = true;
		
		if (m_selectNum[0][0] == true)
		{
			m_stageNum = 0;
			m_selectLoopCount += 0.05f;
			m_stageBalloonPos[1].y= BUIL_BALL_POSY + (sin(m_selectLoopCount)) * 10.0f;
		}
		else if (m_selectNum[0][1] == true)
		{
			m_stageNum = 1;
			m_selectLoopCount += 0.05f;
			m_stageBalloonPos[0].y = BUIL_BALL_POSY + (sin(m_selectLoopCount)) * 10.0f;
		}
		else if (m_selectNum[1][0] == true)
		{
			m_stageNum = 2;
			m_selectLoopCount += 0.05f;
			m_stageBalloonPos[2].y = TRAP_BALL_POSY + (sin(m_selectLoopCount)) * 10.0f;
		}
		else if (m_selectNum[1][1] == true)
		{
			m_stageNum = 3;
			m_selectLoopCount += 0.05f;
			m_stageBalloonPos[3].y = TRAP_BALL_POSY + (sin(m_selectLoopCount)) * 10.0f;
		}
		for (int i = 0; i < 4; i++)
		{
			m_stageBalloon_Sprite[i]->SetPosition(m_stageBalloonPos[i]);
		}

	}
}
