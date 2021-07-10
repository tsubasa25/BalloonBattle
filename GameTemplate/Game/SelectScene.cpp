#include "stdafx.h"
#include "SelectScene.h"
#include "BackGround.h"
#include "GameScene.h"
#include "TitleBack.h"
#include "UIDisplay.h"
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
	DeleteGO(m_okPlayer_Sprite);
	DeleteGO(m_okStok_Sprite);
	for (int i = 0; i < 8; i++)
	{
		DeleteGO(m_playerUI_Sprite[i]);
		DeleteGO(m_stageBalloon_Sprite[i/2]);
	}	
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
	m_arrowPlayer_Sprite->Init("Assets/Image/selectArrow.dds", 100, 200);
	m_arrowPlayer_Sprite->SetPosition(m_arrowPlayerPos);
	m_arrowStock_Sprite=NewGO<SpriteRender>(0);
	m_arrowStock_Sprite->Init("Assets/Image/selectArrow.dds", 100, 200);
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

	return true;
}

void SelectScene::Update()
{
	if (m_titleState==enPlayerNum)
	{
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			m_okPlayer_Sprite = NewGO<SpriteRender>(0);
			m_okPlayer_Sprite->Init("Assets/Image/OK!.dds", 240, 135);
			m_okPlayer_Sprite->SetPosition(m_okPlayerPos);
			m_titleState = enPlayerStock;
		}
		if (g_pad[0]->IsTrigger(enButtonUp))
		{
			m_playerCount++;//�l���𑝂₷
			if (m_playerCount > 8)
			{
				m_playerCount = 2;
			}
		}
		if (g_pad[0]->IsTrigger(enButtonDown))
		{
			m_playerCount--;//�l�������炷
			if (m_playerCount < 2)
			{
				m_playerCount = 8;
			}
		}
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
	}
	else if (m_titleState == enPlayerStock)
	{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		m_okStok_Sprite = NewGO<SpriteRender>(0);
		m_okStok_Sprite->Init("Assets/Image/OK!.dds", 240, 135);
		m_okStok_Sprite->SetPosition(m_okStockPos);
		m_titleState = enStageSelect;
	}
		if (g_pad[0]->IsTrigger(enButtonUp))
		{
			m_playerStock++;//�l���𑝂₷
			if (m_playerStock > 9)
			{
				m_playerStock = 0;
			}
		}
		if (g_pad[0]->IsTrigger(enButtonDown))
		{
			m_playerStock--;//�l�������炷
			if (m_playerStock < 0)
			{
				m_playerStock = 9;
			}
		}
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
	else if (m_titleState==enStageSelect)
	{
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			BackGround* backGround = NewGO<BackGround>(0,"backGround");
			backGround->SetStageNum(m_stageNum);
			GameScene* gameScene = NewGO<GameScene>(0, "gameScene");
			gameScene->SetPlayerCount(m_playerCount);
			gameScene->SetStock(m_playerStock);
			NewGO<UIDisplay>(0, "UIdisplay");//= UIDisplay* UIdisplay 
			TitleBack*titleBack = FindGO<TitleBack>("titleBack");
			titleBack->SetDestroy(true);
			DeleteGO(this);
		}
		if (g_pad[0]->IsTrigger(enButtonUp))
		{
			m_XNum++;
			m_selectLoopCount = 0;
			if (m_XNum > 1)
			{
				m_XNum = 0;
			}
		}
		if (g_pad[0]->IsTrigger(enButtonDown))
		{
			m_XNum--;
			m_selectLoopCount = 0;
			if (m_XNum < 0)
			{
				m_XNum = 1;
			}
		}
		if (g_pad[0]->IsTrigger(enButtonRight))
		{
			m_YNum++;
			m_selectLoopCount = 0;
			if (m_YNum > 1)
			{
				m_YNum = 0;
			}
		}
		if (g_pad[0]->IsTrigger(enButtonLeft))
		{
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