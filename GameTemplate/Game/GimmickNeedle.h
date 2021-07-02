#pragma once
namespace
{
	const int NEEDLE_DOWN_INTERVAL = 400;	//針が出ていない時間
	const int NEEDLE_UP_INTERVAL = 200;	//針が出ている時間
}
class GimmickNeedle	: public IGameObject
{
public:
	bool Start();
	void Update();
	void Move();

	void SetPosition(Vector3 pos) { m_needleBoardPos = pos; }

private:
	SkinModelRender* m_needleModelRender = nullptr;
	SkinModelRender* m_needleBoardModelRender = nullptr;

	Vector3 m_needleBoardPos = {Vector3::Zero};
	Vector3 m_needlePos = { Vector3::Zero };

	Vector3 m_diff = {Vector3::Zero};	//プレイヤーと針の距離

	bool m_isNeedleUp = false;
	int m_needleMoveTimer = 0;	//針の動きを制御するタイマー	
};

