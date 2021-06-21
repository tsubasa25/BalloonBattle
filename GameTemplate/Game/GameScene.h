#pragma once
#include "Player.h"
class GameScene:public IGameObject
{
public:
	~GameScene();
	bool Start();
	void Update();
private:
	int m_playerCount = 4;
	
	Player* player[8] = { nullptr,nullptr, nullptr, nullptr,nullptr,nullptr, nullptr, nullptr };
	Vector3 m_iniPos[8] = { {-600,50,600} ,{600,50,600} ,{-600,50,-600} ,{600,50,-600},	{-400,50,400} ,{400,50,400} ,{-400,50,-400} ,{400,50,-400} };//èâä˙à íu
	PointLight* pointLight[10] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
	bool aa = true;
	int aaNum = 0;
	int m_enemyNum = 0;
public:
	Vector3 GetIniPos(int i) { return m_iniPos[i]; }
	void SetPlayerCount(int num) { m_playerCount = num; }
	int GetPlayerCount() { return m_playerCount; }
};

