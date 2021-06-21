#include "stdafx.h"
#include "WindTurbine.h"
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
	m_rot.SetRotation(Vector3::AxisY, a);
	m_rot.Apply(m_front);
	/*float x = m_front.Dot(Vector3::AxisX);
	m_angle = acosf(x);
	if (m_front.x > 0.0f)
		m_angle *= -1.0f;
	*/
	//m_rot.SetRotation(Vector3::AxisY,m_angle );
	
	m_skinModelRender->SetRotation(m_rot);
}