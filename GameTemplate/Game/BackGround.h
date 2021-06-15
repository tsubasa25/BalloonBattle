#pragma once
class BackGround:public IGameObject
{
public:
	~BackGround();
	bool Start();
	void Update();
private:
	SkinModelRender* m_skinModelRender=nullptr;
	DirectionLight* m_directionLight = nullptr;
	PhysicsStaticObject m_physicsStaticObject;				//CharaConとの当たり判定に使用する静的物理オブジェクト
};

