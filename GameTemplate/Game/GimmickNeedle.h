#pragma once
namespace
{
	const int NEEDLE_DOWN_INTERVAL = 400;	//�j���o�Ă��Ȃ�����
	const int NEEDLE_UP_INTERVAL = 200;	//�j���o�Ă��鎞��
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

	Vector3 m_diff = {Vector3::Zero};	//�v���C���[�Ɛj�̋���

	bool m_isNeedleUp = false;
	int m_needleMoveTimer = 0;	//�j�̓����𐧌䂷��^�C�}�[	
};

