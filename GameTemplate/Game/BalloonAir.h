#pragma once
class Player;
#include "Player.h"
namespace
{
	const int INI_AIR_VOLUME = 70;//���D�̋�C�̗ʂ̏����l
	const int MAX_BALLOON_SIZE = 350;	//���D�̋�C�̗ʂ̍ő��
	const int MIN_BALLOON_SIZE = 10;	//���D�̋�C�̗ʂ̍ŏ���
	const float BRAKE_POWER = 0.1;	//�u���[�L���s�����ۂ�m_moveSpeed�ɂ�����l
	const float AIR_COST_BOOST = 0.5f;	//��C�𕬎˂��Ă���Ƃ��ɁA1�t���[���Ō����C��
}

class BalloonAir : public IGameObject
{
private:
	Player* m_parent = nullptr;
	int m_parentNum = 0;
	float m_airVolume = INI_AIR_VOLUME;//���D�̑傫��(��)

public:
	bool Start();
	void Update();

	void SetParent(Player* p) { m_parent = p; };	//�e�ƂȂ镗�D��ݒ�B
	void SetParentNum(int num) { m_parentNum = num; };
	void Air();	//���D�̋�C�Ɋւ���֐�

	void AddAir(float air);		//air�̒l���A��C������
	void BleedAir(float air);	//air�̒l���A��C�𔲂�

};

