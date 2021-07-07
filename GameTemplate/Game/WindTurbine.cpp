#include "stdafx.h"
#include "WindTurbine.h"
#include "Player.h"
WindTurbine::~WindTurbine()
{

}

bool WindTurbine::Start()
{
	m_WTBaseModelRender = NewGO<SkinModelRender>(0);
	m_WTBaseModelRender->Init("Assets/modelData/WindTurbineBase.tkm");
	m_WTBaseModelRender->SetPosition(m_position);

	m_WTBladesModelRender = NewGO<SkinModelRender>(0);
	m_WTBladesModelRender->Init("Assets/modelData/WindTurbineBlades.tkm");
	m_WTBladesModelRender->SetPosition(m_WTBladesPos);
	m_bladesRot.SetRotation(m_front, m_WTBladesAngle);
	m_WTBladesModelRender->SetRotation(m_bladesRot);

	eff.Init(u"Assets/effect/WindTurbineEff.efk");
	eff.SetPosition(m_WTBladesPos);

	return true;
}

void WindTurbine::Update()
{
	WTMoveTimer++;
	if (WTMoveFlag == false)
	{
		if (WTMoveTimer > WT_NOT_MOVE_INTERVAL)
		{
			WTMoveFlag = true;
			WTMoveTimer = 0;
			eff.Play();
			eff.Update();
		}
	}
	else
	{
		BladesSpin();

		//m_front = { 0.0f,0.0f, 1.0f };//��x�N�g���i�ŏ��Ɍ����Ă������::����K�v�j
		//a += 0.01f;//�񂷃X�s�[�h
		//m_front.Normalize();//���K��
		//m_rot.SetRotation(Vector3::AxisY, a);//a�̕�������
		//m_rot.Apply(m_front);//���ʃx�N�g���̌�����ς���

		//�v���C���[��T��
		QueryGOs<Player>("player", [this](Player* player)->bool {
			m_diff = player->GetPosition() - m_position;//�v���C���[�ƕ��Ԃ̈ʒu�̋������Ƃ�

			if (m_diff.Length() <= 5000) {//5000�ȓ��Ƀv���C���[�������
				m_diff.Normalize();
				float n = m_front.Dot(m_diff);
				m_angle = acosf(n);
				if (m_diff.z < 0) {
					m_angle *= -1;
				}
				if (m_angle <= 0.3 && m_angle >= -0.3) {
					player->AddMoveSpeed(m_front / 2);
				}
			}

			return true;
			});

		//m_WTBladesModelRender->SetRotation(m_rot);

		if (WTMoveTimer > WT_MOVE_INTERVAL)
		{
			WTMoveFlag = false;
			WTMoveTimer = 0;
			m_bladesSpinPower = 0.01f;
		}
	}
}
void WindTurbine::BladesSpin()
{
	if (WTMoveTimer < WT_MOVE_INTERVAL - (WT_MOVE_INTERVAL - 60))
	{
		m_bladesSpinPower *= 1.01f;
		if (m_bladesSpinPower > 1.2f)
			m_bladesSpinPower = 1.2f;
		m_WTBladesAngle += m_bladesSpinPower;

	}
	else if (WTMoveTimer > WT_MOVE_INTERVAL - 60)
	{
		m_bladesSpinPower /= 1.01f;
		if (m_bladesSpinPower < 0.01f)
			m_bladesSpinPower = 0.01f;
		m_WTBladesAngle += m_bladesSpinPower;
	}
	else
		m_WTBladesAngle += m_bladesSpinPower;

	m_bladesRot.SetRotation(m_front, m_WTBladesAngle);
	m_WTBladesModelRender->SetRotation(m_bladesRot);
}