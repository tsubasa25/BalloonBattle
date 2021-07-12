#include "stdafx.h"
#include "GameTimer.h"
#include "GameScene.h"

GameTimer::~GameTimer()
{
	DeleteGO(m_firstPlaceOfTimerSprite);
	DeleteGO(m_tenthPlaceOfTimerSprite);
}

bool GameTimer::Start()
{
	m_timer = TIME_LIMIT;

	m_firstPlaceOfTimerSprite = NewGO<SpriteRender>(0);
	m_firstPlaceOfTimerSprite->SetPosition({30.0f, 300.0f, 0.0f});

	m_tenthPlaceOfTimerSprite = NewGO<SpriteRender>(0);
	m_tenthPlaceOfTimerSprite->SetPosition({ -30.0f, 300.0f, 0.0f });
	
	m_gameScene = FindGO<GameScene>("gameScene");

	SetFirstPlaceOfTimer();
	SetTenthPlaceOfTimer();

	return true;
}

void GameTimer::Update()
{
	if (m_gameScene->GetGameState() != GAME_STATE_BATTLE)
	{
		return;
	}

	if (m_timer > 0.0f)
	{
		m_timer -= g_gameTime->GetFrameDeltaTime();
	}

	if ((int)m_timer != m_oldTimer)
	{
		SetFirstPlaceOfTimer();
		SetTenthPlaceOfTimer();
	}

	m_oldTimer = (int)m_timer;
}

void GameTimer::SetFirstPlaceOfTimer()
{
	int firstPlaceNum = (int)m_timer % 10;
	
	SetNumSprite(m_firstPlaceOfTimerSprite, firstPlaceNum);
}

void GameTimer::SetTenthPlaceOfTimer()
{
	int tenthPlaceNum = (int)m_timer / 10;

	if (m_oldTenthPlaceNum != tenthPlaceNum)
	{
		SetNumSprite(m_tenthPlaceOfTimerSprite, tenthPlaceNum);
		m_oldTenthPlaceNum = tenthPlaceNum;
	}
}

void GameTimer::SetNumSprite(SpriteRender* sprite, int num)
{
	switch (num)
	{
	case 0:
		sprite->Init("Assets/Image/c0.dds", 70, 140);
		break;
	case 1:
		sprite->Init("Assets/Image/c1.dds", 70, 140);
		break;
	case 2:
		sprite->Init("Assets/Image/c2.dds", 70, 140);
		break;
	case 3:
		sprite->Init("Assets/Image/c3.dds", 70, 140);
		break;
	case 4:
		sprite->Init("Assets/Image/c4.dds", 70, 140);
		break;
	case 5:
		sprite->Init("Assets/Image/c5.dds", 70, 140);
		break;
	case 6:
		sprite->Init("Assets/Image/c6.dds", 70, 140);
		break;
	case 7:
		sprite->Init("Assets/Image/c7.dds", 70, 140);
		break;
	case 8:
		sprite->Init("Assets/Image/c8.dds", 70, 140);
		break;
	case 9:
		sprite->Init("Assets/Image/c9.dds", 70, 140);
		break;
	default:
		sprite->Init("Assets/Image/c0.dds", 70, 140);
		break;
	}
}
