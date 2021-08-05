#include "stdafx.h"
#include "GameTimer.h"
#include "GameScene.h"
#include "ResultScene.h"
namespace nsBalloon {
	namespace nsGTConstant
	{
		const int TIME_LIMIT = 100;
	}
	GameTimer::~GameTimer()
	{
		DeleteGO(m_firstPlaceOfTimerSprite);
		DeleteGO(m_tenthPlaceOfTimerSprite);
	}
	bool GameTimer::Start()
	{
		m_timer = nsGTConstant::TIME_LIMIT;

		m_firstPlaceOfTimerSprite = NewGO<SpriteRender>(1);
		SetFirstPlaceOfTimer();
		m_firstPlaceOfTimerSprite->SetPosition({ 30.0f, 300.0f, 0.0f });

		m_tenthPlaceOfTimerSprite = NewGO<SpriteRender>(1);
		SetTenthPlaceOfTimer();
		m_tenthPlaceOfTimerSprite->SetPosition({ -30.0f, 300.0f, 0.0f });

		m_gameScene = FindGO<GameScene>("gameScene");

		return true;
	}

	void GameTimer::Update()
	{
		if (m_gameScene->GetGameState() != nsGSConstant::GAME_STATE_BATTLE)
		{
			return;
		}

		if (m_timer <= 0.0f)
		{
			SetFirstPlaceOfTimer();
			m_gameScene->SetGameState(nsGSConstant::GAME_STATE_RESULT);
			ResultScene* resultScene = NewGO<ResultScene>(0, "resultScene");
			resultScene->SetResultMode(resultScene->GetEnTimeUp());
			QueryGOs<Player>("player", [this](Player* player)->bool {
				player->SetCanMove(false);
				return true;
				});
		}
		else
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
		char filePath[256];
		sprintf(filePath, "Assets/Image/c%d.dds", num);
		sprite->Init(filePath, 70, 140);
	}
}