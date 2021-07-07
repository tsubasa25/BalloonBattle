#pragma once
namespace
{
	const int WT_NOT_MOVE_INTERVAL = 100;	//•—ŽÔ‚ª“®‚¢‚Ä‚¢‚È‚¢ŽžŠÔ
	const int WT_MOVE_INTERVAL = 250;		//•—ŽÔ‚ª“®‚¢‚Ä‚¢‚éŽžŠÔ
}
class WindTurbine :public IGameObject
{
public:
	~WindTurbine();
	bool Start();
	void Update();
	void BladesSpin();

	void SetPosition(Vector3 pos) { m_position = pos; }
	void SetWTBledesPos(Vector3 pos) { m_WTBladesPos = pos; }
private:
	FontRender* m_font;
	Quaternion m_rot = {0.0f,1.0f,0.0f, 0.0f};
	SkinModelRender* m_WTBaseModelRender = nullptr;
	SkinModelRender* m_WTBladesModelRender = nullptr;
	Vector3 m_position = { Vector3::Zero };
	

	float m_angle=0.0f;
	Vector3 m_front = { 0.0f,0.0f, -1.0f };
	float a = 0.0f;
	Vector3 m_diff;
	
	Vector3 m_WTBladesPos = { 0.0f, 200.0f, 0.0f};
	int WTMoveTimer = 0;
	bool WTMoveFlag = false;
	Quaternion m_bladesRot = { 0.0f,0.0f,1.0f, 0.0f };
	float m_bladesSpinPower = 0.01f;
	float m_WTBladesAngle = 1.0f;
	Effect eff;
};

