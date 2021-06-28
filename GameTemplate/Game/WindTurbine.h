#pragma once
class WindTurbine :public IGameObject
{
public:
	~WindTurbine();
	bool Start();
	void Update();

	void SetPosition(Vector3 pos) { m_position = pos; }

private:
	FontRender* m_font;
	Quaternion m_rot = {0.0f,1.0f,0.0f, 0.0f};
	SkinModelRender* m_skinModelRender = nullptr;
	Vector3 m_position = { Vector3::Zero };
	

	float m_angle=0.0f;
	Vector3 m_front = { -1.0f,0.0f, 0.0f };
	float a = 0.0f;
	Vector3 m_diff;
	
};

