#pragma once
#include "WindTurbine.h"

class BackGround:public IGameObject
{
public:
	~BackGround();
	bool Start();
	void Update();
private:
	SkinModelRender* m_skinModelRender=nullptr;
	DirectionLight* m_directionLight = nullptr;
	PhysicsStaticObject m_physicsStaticObject;				//CharaCon�Ƃ̓����蔻��Ɏg�p����ÓI�����I�u�W�F�N�g

	WindTurbine* m_windTurbine = nullptr;

	Level m_level;
};

