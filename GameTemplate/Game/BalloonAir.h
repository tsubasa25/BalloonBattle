#pragma once
class Player;
namespace
{
	const float ADD_AIR_TO_BALLOON_POWER = 3.0f;	//���D��c��܂���Ƃ��ɋ�C�ʂɉ��Z����l�B
	const int MAX_AIR_VOLUME = 500;	//���D�̋�C�̗ʂ̍ő��
	const int MIN_AIR_VOLUME = 30;	//���D�̋�C�̗ʂ̍ŏ���
	const float BRAKE_POWER = 0.1f;	//�u���[�L���s�����ۂ�m_moveSpeed�ɂ�����l
	const float AIR_COST_MOVE = 0.02f;	//L�X�e�B�b�N��|���Ĉړ����Ă���Ƃ��ɁA1�t���[���Ō����C��
	const float AIR_COST_BOOST = 1.0f;	//�����u�[�X�g���Ă���Ƃ��ɁA1�t���[���Ō����C��
	const float AIR_COST_RISE_BOOST = 1.2f;	//�㏸�u�[�X�g���Ă���Ƃ��ɁA1�t���[���Ō����C��
	const float AIR_COST_BRAKE = 0.2f;	//�u���[�L�������Ă���Ƃ��ɁA1�t���[���Ō����C��
	const float ADD_BOOST_POWER = 0.05f;	//�u�[�X�g�ŉ�������Ƃ��ɂ�����l
	const Vector3 RISE_BOOST_POWER = { 0.0f, 1.0f, 0.0f };	//�u�[�X�g�ŏ㏸����Ƃ���Y�����ւ̗�
	const float SOUND_AIR_SE_VOLUME = 0.4f;
}

class BalloonAir : public IGameObject
{
private:
	Player* m_parent = nullptr;
	int m_parentNum = 0;
	float m_airVolume = 0.0f;//���D�̑傫��(��)
	SoundSource* ssAccel = nullptr;
	SoundSource* ssInflate = nullptr;
	SoundSource* ssRise = nullptr;
	SoundSource* ssBrake = nullptr;
	SoundSource* ssDeath = nullptr;

	bool m_inflateSECanPlay = true;
	bool m_inflateSEStopFlag = false;
	bool m_accelSECanPlay = true;
	bool m_accelSEStopFlag = false;
	bool m_riseSECanPlay = true;
	bool m_riseSEStopFlag = false;
	bool m_brakeSECanPlay = true;
	bool m_brakeSEStopFlag = false;

public:
	bool Start();
	void Update();

	void SetParent(Player* p) { m_parent = p; };	//�e�ƂȂ镗�D��ݒ�B
	void SetParentNum(int num) { m_parentNum = num; };
	void Air();	//���D�̋�C�Ɋւ���֐�

	void AddAir(float air);		//air�̒l���A��C������
	void BleedAir(float air);	//air�̒l���A��C�𔲂�

	void SetAirVolume(float air) { m_airVolume = air; };

	void AcceleSEStop() { m_accelSEStopFlag = true; };
	void RiseSEStop() { m_riseSEStopFlag = true; };
	void InflateSEStop() { m_riseSEStopFlag = true; };
	void BrakeSEStop() { m_brakeSEStopFlag = true; };
};

