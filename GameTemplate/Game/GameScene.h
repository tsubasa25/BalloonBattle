#pragma once
#include "Player.h"
namespace
{
	const int GAME_STATE_LOOK_STAGE = 1;
	const int GAME_STATE_START_CALL = 2;
	const int GAME_STATE_BATTLE = 3;
	const Vector3 INI_CAMERA_POS = { 0.0f, 1200.0f, -1800.0f };
	const Vector3 INI_CAMERA_TARGET_POS = { 0,0,-300 };
	const int INI_GAME_START_CALL_TIME = 150;
	const int INI_LOOK_STAGE_TIME = 300;
}
class GameScene:public IGameObject
{
public:
	~GameScene();
	bool Start();
	void Update();
private:
	int m_playerCount = 0;
	int m_stock = 0;

	Player* player[8] = { nullptr,nullptr, nullptr, nullptr,nullptr,nullptr, nullptr, nullptr };
	Vector3 m_iniPos[8] = { {-600,50,600} ,{600,50,600} ,{-600,50,-600} ,{600,50,-600},	{-400,50,400} ,{400,50,400} ,{-400,50,-400} ,{400,50,-400} };//初期位置
	PointLight* pointLight[10] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
	
	bool m_IsAlive[8] = { false,false,false,false,false,false,false,false };//生存確認
	//ライト実験用
	bool aa = true;
	int aaNum = 0;
	
	//エフェクト実験用
	Effect eff;

	FontRender* m_gameStartFontRender = nullptr;
	int m_gameSceneState = 0;

	int m_gameStartCallTimer = INI_GAME_START_CALL_TIME;
	int m_lookStageTimer = INI_LOOK_STAGE_TIME;
	FontRender* m_stageNameFontRender = nullptr;
	Vector2 m_stageNamePos = {Vector2::Zero};

	DirectionLight* m_directionLight = nullptr;

	std::wstring m_stageName = {L"Hoge"};

public:
	Vector3 GetIniPos(int i) { return m_iniPos[i]; }
	void SetPlayerCount(int num) { m_playerCount = num; }
	int GetPlayerCount() { return m_playerCount; }
	//void SetIsAlive(int pNum, bool alive) { m_IsAlive[pNum] = alive; }

void LookStage();
void SetStock(int num) { m_stock = num; }
	int GetStock() { return m_stock; }	void GameStartCall();

	void Retri();
	void SetGameState(int num) { m_gameSceneState = num; };
	int GetGameState() { return m_gameSceneState; };
};

