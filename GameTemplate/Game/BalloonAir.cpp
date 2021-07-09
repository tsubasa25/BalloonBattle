#include "stdafx.h"
#include "BalloonAir.h"
#include "Player.h"
bool BalloonAir::Start()
{
	return true;
}

void BalloonAir::Update()
{
	if (m_parent->GetCanMove() == false)
		return;
	Air();	
	m_parent->SetAirVolume(m_airVolume);
}
void BalloonAir::Air()
{
	Vector3 speedToHorizontal = m_parent->GetMoveSpeed();	//���������ւ̃X�s�[�h(y������0)
	speedToHorizontal.y = 0.0f;

	//�u���[�L�Ƌ�C�����̏���
	if (g_pad[m_parentNum]->IsPress(enButtonB))
	{
		//�v���C���[�������Ă���Ƃ���B�{�^���������ƁA
		if (speedToHorizontal.Length() > 0.0f)
		{
			//�u���[�L��������B
			Vector3 brakeSpeed = m_parent->GetMoveSpeed();
			brakeSpeed.y = 0;
			brakeSpeed *= BRAKE_POWER;
			brakeSpeed *= -1.0f;	//���D��m_moveSpeed�Ɍ��Z����̂�-1��������B
			m_parent->AddMoveSpeed(brakeSpeed);
			BleedAir(speedToHorizontal.Length() * AIR_COST_BRAKE);	//�u���[�L�̃f�����b�g�Ƃ��ċ�C��������
		}
		else
		{
			//�~�܂��Ă���Ƃ���B�{�^���������ƁA�c�ށB
			AddAir(ADD_AIR_TO_BALLOON_POWER);
			
			if (InflateFlg == false ) {
				InflateFlg = true;
				ssInflate = NewGO<SoundSource>(0);
				ssInflate->Init(L"Assets/sound/���D��c��܂��鉹.wav");
				ssInflate->Play(true);
			}
			if (m_airVolume >= MAX_AIR_VOLUME) {
				DeleteGO(ssInflate);
			}
		}
	}
	else if (InflateFlg == true) {
		DeleteGO(ssInflate);
		InflateFlg = false;
	}

	//�v���C���[���X�e�B�b�N��|���Ă���Ƃ�
	if (g_pad[m_parentNum]->GetLStickXF() != 0.0f
		|| g_pad[m_parentNum]->GetLStickYF() != 0.0f)
	{
		//L�X�e�B�b�N�̌X���̑傫���ɉ����āA��C��������B
		Vector3 LStickTilt = {
			(g_pad[m_parentNum]->GetLStickXF()),
			(g_pad[m_parentNum]->GetLStickYF()),
			0.0f
		};
		BleedAir(LStickTilt.Length() * AIR_COST_MOVE);

		//A�{�^���������ꂽ��A��C�𕬎˂��Ĉ�C�ɉ����B
		if (g_pad[m_parentNum]->IsPress(enButtonA))
		{
			Vector3 boostSpeed = m_parent->GetMoveSpeed();		
			boostSpeed.y = 0.0f;

			boostSpeed.x *= ADD_BOOST_POWER;
			boostSpeed.z *= ADD_BOOST_POWER;

			m_parent->AddMoveSpeed(boostSpeed);

			//��C�����ʔ�����B
			BleedAir(AIR_COST_BOOST);

			if (m_accelSECanPlay == true) {
				m_accelSECanPlay = false;
				ssAccel = NewGO<SoundSource>(0);
				ssAccel->Init(L"Assets/sound/���D���������鉹.wav");
				ssAccel->Play(true);
			}
		}
	}
	if (!g_pad[m_parentNum]->IsPress(enButtonA))
	{
		m_accelSEStopFlag = true;
	}
	if (m_accelSEStopFlag == true)
	{
		DeleteGO(ssAccel);
		m_accelSEStopFlag = false;
		m_accelSECanPlay = true;
	}
	
	if (g_pad[m_parentNum]->IsPress(enButtonY))
	{

		m_parent->AddMoveSpeed(RISE_BOOST_POWER);
		
		//��C�����ʔ�����B
		BleedAir(AIR_COST_RISE_BOOST);
		if (m_riseSECanPlay == true) {
			m_riseSECanPlay = false;
			ssRise = NewGO<SoundSource>(0);
			ssRise->Init(L"Assets/sound/���D���������鉹.wav");
			ssRise->Play(true);
		}
	}
	if (!g_pad[m_parentNum]->IsPress(enButtonY))
	{
		m_riseSEStopFlag = true;
	}
	if (m_riseSEStopFlag == true)
	{
		DeleteGO(ssRise);
		m_riseSEStopFlag = false;
		m_riseSECanPlay = true;
	}
}


//air�̒l���A���D�ɋ�C��������
void BalloonAir::AddAir(float air)
{
	m_airVolume += air;
	if (m_airVolume > MAX_AIR_VOLUME)	//�ő�T�C�Y���͑傫���Ȃ�Ȃ��B
		m_airVolume = MAX_AIR_VOLUME;
	
}
//air�̒l���A���D�̋�C�𔲂�
void  BalloonAir::BleedAir(float air)
{
	m_airVolume -= air;
	if (m_airVolume < MIN_AIR_VOLUME)	//�ŏ��T�C�Y��菬�����Ȃ�����A���S����B
	{
		m_parent->PlayerDeath();
		ssDeath = NewGO<SoundSource>(0);
		ssDeath->Init(L"Assets/sound/���D�̈ނ�Ŏ��񂾉�.wav");
		ssDeath->Play(false);
	}
}