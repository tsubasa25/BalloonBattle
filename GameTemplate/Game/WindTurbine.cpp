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
	a += 0.01f;
	
	m_front.Normalize();
	/*m_rot.SetRotation(Vector3::AxisY, a);
	m_rot.Apply(m_front);*/

	QueryGOs<Player>("player", [this](Player* player)->bool {
		m_diff = player->GetPosition()- m_position;
		
		if (m_diff.Length() <= 5000) {


			m_diff.Normalize();
			float n = m_front.Dot(m_diff);
			float angle = acosf(n);
			/*if (m_diff.z < 0) {
				angle *= -1;
			}*/
			if (angle <= 0.03 && angle >= -0.03) {
				player->SetMoveSpeed(m_front*5);
				
			}
		}

		return true;
		});
	//m_skinModelRender->SetRotation(m_rot);
}