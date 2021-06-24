#include "stdafx.h"
#include "BalloonAir.h"

bool BalloonAir::Start()
{

	return true;
}

void BalloonAir::Update()
{
	Air();
	m_parent->SetAirVolume(m_airVolume);
}
void BalloonAir::Air()
{
	Vector3 speedToHorizontal = m_parent->GetMoveSpeed();	//���������ւ̃X�s�[�h(y������0)
	speedToHorizontal.y = 0;

	//�u���[�L�Ƌ�C�����̏���
	if (g_pad[m_parentNum]->IsPress(enButtonB))
	{
		if (speedToHorizontal.Length() > 0.0f)
		{
			//�u���[�L��������B
			Vector3 brakeSpeed = m_parent->GetMoveSpeed();
			brakeSpeed.y = 0;
			brakeSpeed *= BRAKE_POWER;
			brakeSpeed *= -1.0f;	//���D��m_moveSpeed�Ɍ��Z����̂�-1��������B
			m_parent->AddMoveSpeed(brakeSpeed);
			BleedAir(speedToHorizontal.Length() * BRAKE_POWER);	//�u���[�L�̃f�����b�g�Ƃ��ċ�C��������
		}
		else
		{
			//�~�܂��Ă���Ƃ���B�{�^���������ƁA�c�ށB
			AddAir(1.0f);
		}
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
		BleedAir(LStickTilt.Length() * 0.02f);

		//A�{�^���������ꂽ��A��C�𕬎˂��Ĉ�C�ɉ����B
		if (g_pad[0]->IsPress(enButtonA))
		{
			Vector3 boostSpeed = m_parent->GetMoveSpeed();		
			boostSpeed.y = 0.0f;

			boostSpeed.x *= 0.05f;
			boostSpeed.z *= 0.05f;

			m_parent->AddMoveSpeed(boostSpeed);

			//��C�����ʔ�����B
			BleedAir(AIR_COST_BOOST);
		}
	}
	if (g_pad[m_parentNum]->IsPress(enButtonY))
	{
		m_parent->AddMoveSpeed({0.0f,1.0f,0.0f});
		
		//��C�����ʔ�����B
		BleedAir(AIR_COST_BOOST);
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
	if (m_airVolume < MIN_AIR_VOLUME)	//�ŏ��T�C�Y���͏������Ȃ�Ȃ��B
		m_airVolume = MIN_AIR_VOLUME;
}