#pragma once
class Player:public IGameObject
{
private:
	
	Vector3 m_moveSpeed = {Vector3::Zero};
	Vector3 m_position = { Vector3::Zero };
	
	Vector3 m_scale = { Vector3::Zero };
	int m_playerNum = 0;

	FontRender* m_PosX_font = NewGO<FontRender>(0);
	FontRender* m_PosZ_font = NewGO<FontRender>(0);
	
public:
	SkinModelRender* m_skinModelRender = nullptr;
	~Player();
	bool Start();
	void Update();

	void SetPlayerNum(int num) { m_playerNum = num; }
	int GetPlayerNum() { return m_playerNum; }

	void SetMoveSpeed(Vector3 speed) { m_moveSpeed += speed; }
	Vector3 GetMoveSpeed() { return m_moveSpeed; }

	void SetScale(Vector3 scale) { m_scale = scale; }
	Vector3 GetScale() { return m_scale; }

	void SetPosition(Vector3 position) { m_position = position; }
	Vector3 GetPosition() { return m_position; }
	/*float GetPositionX() { return m_position.x; }
	float GetPositionZ() { return m_position.z; }*/

	void SetAccele(Vector3 accele) { m_accele += accele; }
	Vector3 GetAccele() { return m_accele; }

	void SetDecele(Vector3 decele) { m_decele = decele; }
	Vector3 GetDecele() { return m_decele; }

	Vector3 Decele(Vector3 decele);
	
	Vector3 m_accele;
	Vector3 m_decele;

	void Move();

	void Debug();
};

