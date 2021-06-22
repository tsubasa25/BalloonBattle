#pragma once
#include "Player.h"
class GameScene:public IGameObject
{
public:
	~GameScene();
	bool Start();
	void Update();
private:
	int m_playerCount = 8;
	
	Player* player[8] = { nullptr,nullptr, nullptr, nullptr,nullptr,nullptr, nullptr, nullptr };
	Vector3 m_iniPos[8] = { {-600,50,600} ,{600,50,600} ,{-600,50,-600} ,{600,50,-600},	{-400,50,400} ,{400,50,400} ,{-400,50,-400} ,{400,50,-400} };//初期位置
	PointLight* pointLight[10] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
	
	bool m_IsAlive[8] = { false,false,false,false,false,false,false,false };//生存確認
	//ライト実験用
	bool aa = true;
	int aaNum = 0;
	

public:
	Vector3 GetIniPos(int i) { return m_iniPos[i]; }
	void SetPlayerCount(int num) { m_playerCount = num; }
	int GetPlayerCount() { return m_playerCount; }
	void SetIsAlive(int pNum, bool alive) { m_IsAlive[pNum] = alive; }
};

