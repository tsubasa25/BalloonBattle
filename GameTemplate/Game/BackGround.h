#pragma once
#include "WindTurbine.h"
class GameScene;

class BackGround:public IGameObject
{
public:
	~BackGround();
	bool Start();
	void Update();
	//Vector3 GetIniSpawnPosition();
private:
	SkinModelRender* m_skinModelRender=nullptr;
	DirectionLight* m_directionLight = nullptr;
	PhysicsStaticObject m_physicsStaticObject;				//CharaCon�Ƃ̓����蔻��Ɏg�p����ÓI�����I�u�W�F�N�g

	WindTurbine* m_windTurbine = nullptr;

	GameScene* m_gameScene = nullptr;
	Level m_level;

	Vector3 m_spawnPos[8]{Vector3::Zero,Vector3::Zero,Vector3::Zero,Vector3::Zero,Vector3::Zero,Vector3::Zero,Vector3::Zero,Vector3::Zero, };

};

