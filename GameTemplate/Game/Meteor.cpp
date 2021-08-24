#include "stdafx.h"
#include "Meteor.h"
#include "Player.h"
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
			//プレイヤーを探す
			QueryGOs<Player>("player", [this](Player* player)->bool {
				//プレイヤーと針の位置の距離をとる				
				Vector3 diff = player->GetPosition() - m_position;
				if (diff.Length() < 50.f)
				{
					player->BreakBalloon();
					player->PlayerDeath();
					SoundSource* ss = NewGO<SoundSource>(0);
					ss->Init(L"Assets/sound/風船の割れる音.wav");
					ss->Play(false);
				}
				return true;
				});
		}
		m_position -= m_diffVec;
		m_position.y -= nsMConstant::LANDING_SPEED;
		m_skinModelRender->SetPosition(m_position);	
		
		m_fireEff.SetPosition(m_position);
		m_fireEff.Update();
	}
}