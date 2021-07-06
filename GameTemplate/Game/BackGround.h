#pragma once
#include "WindTurbine.h"
class GameScene;
class Player;
class GimmickNeedle;

namespace
{
	const int RESPAWN_POSITION_NUM = 8;	//���X�|�[���n�_�̑���
	const float RESPAWN_POSITION_HEIGHT = 800.0f;	//���X�|�[������Ƃ��Ƀv���C���[���~��Ă��鍂���B
}


class BackGround:public IGameObject
{
public:
	~BackGround();
	bool Start();
	void Update();
Vector3 GetRespawnPosition(int ResPlNum);	//���X�|�[���������v���C���[�̔ԍ���n�����ƂŁA���X�|�[���ʒu���v�Z����B
void SetStageNum(int num) { m_stageNum = num; }
	//Vector3 GetIniSpawnPosition();


private:
	SkinModelRender* m_skinModelRender=nullptr;
	DirectionLight* m_directionLight = nullptr;
	PhysicsStaticObject m_physicsStaticObject;				//CharaCon�Ƃ̓����蔻��Ɏg�p����ÓI�����I�u�W�F�N�g

	WindTurbine* m_windTurbine = nullptr;

	GameScene* m_gameScene = nullptr;
	Level m_level;

	Vector3 m_spawnPos[RESPAWN_POSITION_NUM]{Vector3::Zero,Vector3::Zero,Vector3::Zero,Vector3::Zero,Vector3::Zero,Vector3::Zero,Vector3::Zero,Vector3::Zero, };

	Vector3 m_enemyMiddlePos = { Vector3::Zero };	//���v���C���[�̃|�W�V�����̕��ϒn�_

	int m_respawnPlayerNum = 0;	//���X�|�[������v���C���[�̔ԍ�

	GimmickNeedle* m_needle = nullptr;

	int m_stageNum = 0;
};

