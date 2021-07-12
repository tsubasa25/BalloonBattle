#pragma once
class GameScene;
namespace
{
	const int TIME_LIMIT = 100;
}

class GameTimer	: public IGameObject
{
private:
	GameScene* m_gameScene = nullptr;

	float m_timer = 0;
	int m_oldTimer = 0;

	int m_oldTenthPlaceNum = 0;

	SpriteRender* m_firstPlaceOfTimerSprite = nullptr;
	SpriteRender* m_tenthPlaceOfTimerSprite = nullptr;

public:
	~GameTimer();
	bool Start();
	void Update();

	void SetFirstPlaceOfTimer();
	void SetTenthPlaceOfTimer();
	
	void SetNumSprite(SpriteRender* sprite, int num);

};

