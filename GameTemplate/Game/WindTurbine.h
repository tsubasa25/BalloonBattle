#pragma once
class WindTurbine :public IGameObject
{
public:
	~WindTurbine();
	bool Start();
	void Update();


private:
	SkinModelRender* m_skinModelRender = nullptr;
	Vector3 m_position = { Vector3::Zero };
	void SetPosition(Vector3 pos) { m_skinModelRender->SetPosition(pos); }
};

