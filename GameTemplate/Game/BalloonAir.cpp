#include "stdafx.h"
#include "BalloonAir.h"
#include "Player.h"

BalloonAir::~BalloonAir()
{
	DeleteGO(m_parent);
if(ssAccel != nullptr)
		DeleteGO(ssAccel);
	if (ssInflate != nullptr)
		DeleteGO(ssInflate);
	if (ssRise != nullptr)
		DeleteGO(ssRise);
	if (ssBrake != nullptr)
		DeleteGO(ssBrake);
	if (ssDeath != nullptr)
		DeleteGO(ssDeath);}

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
			if (m_brakeSECanPlay == true) {
				m_brakeSECanPlay = false;
				m_ssBrake = NewGO<SoundSource>(0);
				m_ssBrake->Init(L"Assets/sound/���D���������鉹.wav");
				m_ssBrake->SetVolume(SOUND_AIR_SE_VOLUME);
				m_ssBrake->Play(true);
			}
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
			DeleteGO(m_ssBrake);
			//�~�܂��Ă���Ƃ���B�{�^���������ƁA�c�ށB
			AddAir(ADD_AIR_TO_BALLOON_POWER);

			if (m_inflateSECanPlay == true ) {
				m_inflateSECanPlay = false;
				m_ssInflate = NewGO<SoundSource>(0);
				m_ssInflate->Init(L"Assets/sound/���D��c��܂��鉹.wav");
				m_ssInflate->SetVolume(SOUND_AIR_SE_VOLUME);
				m_ssInflate->Play(true);
			}
			if (m_airVolume >= MAX_AIR_VOLUME) {
				DeleteGO(m_ssInflate);
			}
		}
	}
	if (!g_pad[m_parentNum]->IsPress(enButtonB))
	{
		m_brakeSEStopFlag = true;
		m_inflateSEStopFlag = true;
	}
	if (m_brakeSEStopFlag == true)
	{
		DeleteGO(m_ssBrake);
		m_brakeSEStopFlag = false;
		m_brakeSECanPlay = true;
	}
	if (m_inflateSEStopFlag == true)
	{
		DeleteGO(m_ssInflate);
		m_inflateSEStopFlag = false;
		m_inflateSECanPlay = true;
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

			//�G�t�F�N�g
			Effect boostEff;
			boostEff.Init(u"Assets/effect/BoostEff.efk");
			boostEff.Play();
			boostEff.SetPosition(m_parent->GetPosition());
			boostEff.Update();

			if (m_accelSECanPlay == true) {
				m_accelSECanPlay = false;
				m_ssAccel = NewGO<SoundSource>(0);
				m_ssAccel->Init(L"Assets/sound/���D���������鉹.wav");
				m_ssAccel->SetVolume(SOUND_AIR_SE_VOLUME);
				m_ssAccel->Play(true);
			}
		}
	}
	if (!g_pad[m_parentNum]->IsPress(enButtonA))
	{
		m_accelSEStopFlag = true;
	}
	if (m_accelSEStopFlag == true)
	{
		DeleteGO(m_ssAccel);
		m_accelSEStopFlag = false;
		m_accelSECanPlay = true;
	}
	
	if (g_pad[m_parentNum]->IsPress(enButtonY))
	{

		m_parent->AddMoveSpeed(RISE_BOOST_POWER);
		
		//��C�����ʔ�����B
		BleedAir(AIR_COST_RISE_BOOST);

		//�G�t�F�N�g��A�{�^���̃u�[�X�g�Ɣ��Ȃ��悤�ɂ���B
		if (!g_pad[m_parentNum]->IsPress(enButtonA))
		{
			Effect boostEff;
			boostEff.Init(u"Assets/effect/BoostRiseEff.efk");
			boostEff.Play();
			boostEff.SetPosition(m_parent->GetPosition());
			Quaternion effQRot;
			effQRot.SetRotation(Vector3::AxisX, 90.0f);
			boostEff.SetRotation(effQRot);
			boostEff.Update();
		}

		if (m_riseSECanPlay == true) {
			m_riseSECanPlay = false;
			m_ssRise = NewGO<SoundSource>(0);
			m_ssRise->Init(L"Assets/sound/���D���������鉹.wav");
			m_ssRise->SetVolume(SOUND_AIR_SE_VOLUME);
			m_ssRise->Play(true);
		}
	}
	if (!g_pad[m_parentNum]->IsPress(enButtonY))
	{
		m_riseSEStopFlag = true;
	}
	if (m_riseSEStopFlag == true)
	{
		DeleteGO(m_ssRise);
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
		m_ssDeath = NewGO<SoundSource>(0);
		m_ssDeath->Init(L"Assets/sound/���D�̈ނ�Ŏ��񂾉�.wav");
		m_ssDeath->SetVolume(SOUND_AIR_SE_VOLUME);
		m_ssDeath->Play(false);

		/*Effect soulEff;
		soulEff.Init(u"Assets/effect/SoulRise.efk");
		soulEff.SetPosition(m_parent->GetPosition());
		soulEff.SetScale({ 3.0f,3.0f,3.0f });
		soulEff.Play();
		soulEff.Update();*/

	}
}