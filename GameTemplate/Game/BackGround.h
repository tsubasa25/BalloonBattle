#pragma once
#include "WindTurbine.h"
class Sky;
class GameScene;
class Player;
class GimmickNeedle;

namespace
{
	const int RESPAWN_POSITION_NUM = 8;	//リスポーン地点の総数
	const float RESPAWN_POSITION_HEIGHT = 800.0f;	//リスポーンするときにプレイヤーが降りてくる高さ。
	const std::wstring STAGE_ZERO_NAME = { L"SkyIsLand Stage" };
	const std::wstring STAGE_ONE_NAME = { L"Building Stage" };
	const std::wstring STAGE_TWO_NAME = { L"Trap Stage" };
	const float SOUND_MAP_BGM_VOLUME = 0.2f;
}


class BackGround:public IGameObject
{
private:
	int m_stageNum = 0;
public:
	~BackGround();
	BackGround();
	bool Start();
	void Update();

	Vector3 GetRespawnPosition(int ResPlNum);	//リスポーンしたいプレイヤーの番号を渡すことで、リスポーン位置を計算する。
	void SetStageNum(int num) { m_stageNum = num; };
	int GetStageNum() { return m_stageNum; };
	Vector3 GetWTBladesPos() { return m_WTBladesPos; };
	//Vector3 GetIniSpawnPosition();
	void SetIniPosition();
	std::wstring GetStageName() { return m_stageName; };

private:
	Sky* m_sky = nullptr;

	SkinModelRender* m_skinModelRender = nullptr;
	
	PhysicsStaticObject m_physicsStaticObject;				//CharaConとの当たり判定に使用する静的物理オブジェクト

	WindTurbine* m_windTurbine = nullptr;

	GameScene* m_gameScene = nullptr;
	Level m_level;

	Vector3 m_spawnPos[RESPAWN_POSITION_NUM]{Vector3::Zero,Vector3::Zero,Vector3::Zero,Vector3::Zero,Vector3::Zero,Vector3::Zero,Vector3::Zero,Vector3::Zero, };
	bool m_canRespawn[RESPAWN_POSITION_NUM]{true,true,true,true,true,true,true,true};
	int m_canRespawnInterval[RESPAWN_POSITION_NUM]{0,0,0,0,0,0,0,0};


	Vector3 m_WTBladesPos = {Vector3::Zero};

	Vector3 m_enemyMiddlePos = { Vector3::Zero };	//他プレイヤーのポジションの平均地点

	int m_respawnPlayerNum = 0;	//リスポーンするプレイヤーの番号

	GimmickNeedle* m_needle = nullptr;

	std::wstring m_stageName = {L"Hoge"};

	SoundSource* m_map1BGM = nullptr;
	SoundSource* m_map2BGM = nullptr;
	SoundSource* m_map3BGM = nullptr;
};

