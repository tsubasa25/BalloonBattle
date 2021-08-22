#include "stdafx.h"
#include "Meteor.h"
namespace nsBalloon {
	Meteor::~Meteor()
	{
		DeleteGO(m_skinModelRender);		
	}
	bool Meteor::Start()
	{
		m_skinModelRender = NewGO<SkinModelRender>(0);
		m_skinModelRender->Init("Assets/modelData/Meteor.tkm");
		m_diffVec = m_position - m_tilePosition;
		
		Vector3 diffNormal = m_diffVec;
		Vector3 diffNormalY = m_diffVec;		
		diffNormalY.Normalize();		
		Quaternion rot, rotY;
		diffNormalY.z *= -1;
		diffNormalY.x *= -1;
		rotY.SetRotation(diffNormalY, Vector3::AxisY);		
		rot.Multiply(rotY);
		m_fireEff.SetRotation(rot);
		m_diffVec.y = 0;
		m_diffVec /= (2000 / nsMConstant::LANDING_SPEED);
		m_fireEff.Init(u"Assets/effect/FireEff.efk");
		m_fireEff.Play();
		return true;
	}
	void Meteor::Update()
	{
		Landing();
	}
	void Meteor::Landing()
	{
		if (m_position.y < -500.f) {
			DeleteGO(this);
		}
		if (m_position.y == 0.f) {
			
		}
		m_position -= m_diffVec;
		m_position.y -= nsMConstant::LANDING_SPEED;
		m_skinModelRender->SetPosition(m_position);	
		
		m_fireEff.SetPosition(m_position);
		m_fireEff.Update();
	}
}