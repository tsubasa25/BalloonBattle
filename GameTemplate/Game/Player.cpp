#include "stdafx.h"
#include "Player.h"
Player::~Player()
{

}
bool Player::Start()
{
	m_skinModelRender = NewGO<SkinModelRender>(0);
	if (GetPlayerNum() == 0) {
		m_skinModelRender->Init("Assets/modelData/Ballon.tkm");
	}
	else if (GetPlayerNum() == 1) {
		m_skinModelRender->Init("Assets/modelData/Ballon2.tkm");
	}
	
	return true;
}
void Player::Update()
{
	Move();
	Debug(GetPlayerNum());

}

Vector3 Player::Decele(Vector3 speed)
{
	Vector3 speedVec = speed;
	
	if (speed.Length() > 0.0f) {		
		 return speedVec*-0.05;
	}
	else
		return Vector3::Zero;
}
void Player::Move()
{
	
	SetAccele({ g_pad[GetPlayerNum()]->GetLStickXF() * -1.4f,0,0 });
	SetAccele({ 0,0,g_pad[GetPlayerNum()]->GetLStickYF() * -1.4f });
	SetAccele(Decele(GetAccele()));

	SetMoveSpeed(GetAccele());
	m_skinModelRender->SetPosition(GetMoveSpeed());
	if (m_skinModelRender->GetPositionX() > m_StageWidth || m_skinModelRender->GetPositionX() < -m_StageWidth)
	{
		SetAcceleX(0);
		SetMoveSpeedX(0);
		m_skinModelRender->SetPositionX(GetStageWidth());
	}
	
	if (m_skinModelRender->GetPositionZ() > m_StageDepth || m_skinModelRender->GetPositionZ() < -m_StageDepth)
	{		
		SetAcceleZ(0);
		SetMoveSpeedZ(0);
		m_skinModelRender->SetPositionZ(GetStageDepth());
	}
	
}
void Player::Debug(int pNum)
{	
	if (pNum == 0) {
		m_PosX_font->SetPosition({ -500,100 });
		m_PosZ_font->SetPosition({ -500,0 });
	}
	else {
		m_PosX_font->SetPosition({ 500,100 });
		m_PosZ_font->SetPosition({ 500,0 });
	}
	m_PosX_font->SetText(std::to_wstring(int(m_skinModelRender->GetPositionX())));	
	m_PosZ_font->SetText(std::to_wstring(int(m_skinModelRender->GetPositionZ())));
}