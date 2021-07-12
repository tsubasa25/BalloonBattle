#pragma once
namespace
{
	int TIME_LIMIT = 100;

}

class GameTimer	: public IGameObject
{
private:
	~GameTimer();
	bool Start();
	void Update();

	void SetFirstPlaceOfTimer();
	void SetTenthPlaceOfTimer();

public:

	int m_timer = 0;
	int m_oldTimer = 0;

	SpriteRender* m_firstPlaceOfTimerSprite = nullptr;
	SpriteRender* m_tenthPlaceOfTimerSprite = nullptr;
};

