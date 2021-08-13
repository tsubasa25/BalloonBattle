#include "stdafx.h"
#include "WindTurbine.h"
#include "Player.h"
#include "BackGround.h"
#include "GameScene.h"
namespace nsBalloon {
	WindTurbine::~WindTurbine()
	{
		DeleteGO(m_WTBaseModelRender);
		DeleteGO(m_WTBladesModelRender);
	}

	bool WindTurbine::Start()
	{
		m_gameScene = FindGO<GameScene>("gameScene");

		BackGround* backGround = FindGO<BackGround>("backGround");
		m_WTBladesPos = backGround->GetWTBladesPos();

		m_WTBaseModelRender = NewGO<SkinModelRender>(0);
		m_WTBaseModelRender->Init("Assets/modelData/WindTurbineBase.tkm");
		m_WTBaseModelRender->SetPosition(m_position);

		m_WTBladesModelRender = NewGO<SkinModelRender>(0);
		m_WTBladesModelRender->Init("Assets/modelData/WindTurbineBlades.tkm");
		m_WTBladesModelRender->SetPosition(m_WTBladesPos);
		m_bladesRot.SetRotation(m_frontY, m_WTBladesAngle);
		m_WTBladesModelRender->SetRotation(m_bladesRot);
		m_rotZ.SetRotation(Vector3::AxisZ, 0);//a�̕�����Z����
		eff.Init(u"Assets/effect/WindTurbineEff.efk");
		eff.SetPosition(m_WTBladesPos);
		m_bladesSpinPower = 0.01f;
		
		return true;
	}

	void WindTurbine::Update()
	{
		m_position.x += 0.1f;
		m_WTBaseModelRender->SetPosition(m_position);
		if (m_gameScene->GetGameState() != nsGSConstant::GAME_STATE_BATTLE)
			WTMoveTimer = 0;

		m_frontY = { 0.0f, 0.0f, -1.0f };//��x�N�g���i�ŏ��Ɍ����Ă������::����K�v�j
		a += 0.01f;//�񂷃X�s�[�h
		m_rotY.SetRotation(Vector3::AxisY, a);//a�̕�����Y����
		m_frontZ.y = 0;
		m_rotY.Apply(m_frontY);
		m_rot.Multiply(m_rotZ, m_rotY);
		m_WTBladesModelRender->SetRotation(m_rot);
		m_WTBaseModelRender->SetRotation(m_rotY);

		WTMoveTimer++;//���[�v�J�E���g
		if (WTMoveFlag == false)//
		{
			if (WTMoveTimer > nsWTConstant::WT_NOT_MOVE_INTERVAL)
			{
				WTMoveFlag = true;
				WTMoveTimer = 0;
				eff.Play();
				eff.SetRotation(m_rotY);
				eff.Update();
			}
		}

		else//�u���[�h����
		{
			BladesSpin();
			eff.SetRotation(m_rotY);
			eff.Update();

			//�v���C���[��T��
			QueryGOs<Player>("player", [this](Player* player)->bool {
				m_diff = player->GetPosition() - m_position;//�v���C���[�ƕ��Ԃ̈ʒu�̋������Ƃ�

				if (m_diff.Length() <= 5000) {//5000�ȓ��Ƀv���C���[�������
					m_diff.Normalize();
					float n = m_frontY.Dot(m_diff);
					m_angle = acosf(n);
					if (m_diff.z < 0) {
						m_angle *= -1;
					}
					if (m_angle <= 1.0f && m_angle >= -1.0f) {
						player->AddMoveSpeed(m_frontY / 2);
						//player->AddMoveSpeed(m_frontY * player->GetAirVolume() / 20);
					}
				}

				return true;
				});



			if (WTMoveTimer > nsWTConstant::WT_MOVE_INTERVAL)
			{
				WTMoveFlag = false;
				WTMoveTimer = 0;
				m_bladesSpinPower = 0.01f;
			}
		}
	}
	void WindTurbine::BladesSpin()//�u���[�h����
	{
		if (WTMoveTimer < nsWTConstant::WT_MOVE_INTERVAL - (nsWTConstant::WT_MOVE_INTERVAL - 60))
		{
			m_bladesSpinPower *= 1.07f;
			if (m_bladesSpinPower > 1.2f)
				m_bladesSpinPower = 1.2f;
			m_WTBladesAngle += m_bladesSpinPower;

		}
		else if (WTMoveTimer > nsWTConstant::WT_MOVE_INTERVAL - 60)
		{
			m_bladesSpinPower /= 1.07f;
			if (m_bladesSpinPower < 0.01f)
				m_bladesSpinPower = 0.01f;
			m_WTBladesAngle += m_bladesSpinPower;
		}
		else
			m_WTBladesAngle += m_bladesSpinPower;

		m_frontZ = { 0.0f ,0.0f,0.0f };
		b += 0.3f;
		m_rotZ.SetRotation(Vector3::AxisZ, m_WTBladesAngle);//a�̕�����Z����
		m_frontZ.x = 0;
		m_rotZ.Apply(m_frontZ);
	}
}