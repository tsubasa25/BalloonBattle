#pragma once
class Player:public IGameObject
{
private:
	
	Vector3 m_position;
	Vector3 m_speed;
	Vector3 m_scale;
	int m_playerNum = 1;
public:
	SkinModelRender* m_player = nullptr;
	~Player();
	bool Start();
	void Update();

	void SetPlayerNum(int num) { m_playerNum = num; }
	int GetPlayerNum() { return m_playerNum; }

	void SetPlayerPosition(Vector3 position) { m_position = position; }
	Vector3 GetPlayerPosition() { return m_position; }
	Vector3 position = { Vector3::Zero };
	Vector3 LightPos = { Vector3::Zero };
};

