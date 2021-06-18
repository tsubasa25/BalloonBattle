#pragma once
#include "Player.h"
class GameScene:public IGameObject
{
public:
	~GameScene();
	bool Start();
	void Update();
private:
	//int m_playerCount = 4;
	Player* player[4] = { nullptr,nullptr, nullptr, nullptr };
	Vector3 m_iniPos[4] = { {100,50,100} ,{-100,50,100} ,{100,50,-100} ,{-100,50,-100} };//èâä˙à íu
	int m_enemyNum = 0;
public:
	Vector3 GetIniPos(int i) { return m_iniPos[i]; }
};

