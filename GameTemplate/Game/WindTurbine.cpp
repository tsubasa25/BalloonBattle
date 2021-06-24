#include "stdafx.h"
#include "WindTurbine.h"
#include "Player.h"
WindTurbine::~WindTurbine()
{

}

bool WindTurbine::Start()
{
	m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->Init("Assets/modelData/WindTurbine.tkm");
	
	SetPosition(m_position);


	return true;
}

void WindTurbine::Update()
{
	m_front={ -1.0f,0.0f, 0.0f };//��x�N�g���i�ŏ��Ɍ����Ă������::����K�v�j
	a += 0.01f;//�񂷃X�s�[�h
	
	m_front.Normalize();//���K��
	m_rot.SetRotation(Vector3::AxisY, a);//a�̕�������
	m_rot.Apply(m_front);//���ʃx�N�g���̌�����ς���
	
	//�v���C���[��T��
	QueryGOs<Player>("player", [this](Player* player)->bool {
		m_diff = player->GetPosition()- m_position;//�v���C���[�ƕ��Ԃ̈ʒu�̋������Ƃ�
		
		if (m_diff.Length() <= 5000) {//5000�ȓ��Ƀv���C���[�������
			m_diff.Normalize();
			float n = m_front.Dot(m_diff);
			m_angle = acosf(n);
			if (m_diff.z < 0) {
				m_angle *= -1;
			}
			if (m_angle <= 0.3 && m_angle >= -0.3) {
				player->AddMoveSpeed(m_front/2);
			}
		}

		return true;
	});
	m_skinModelRender->SetRotation(m_rot);	
}