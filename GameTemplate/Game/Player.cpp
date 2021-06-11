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
	

}

Vector3 Player::Decele(Vector3 speed)
{
	Vector3 speedVec = speed;
	
	if (speed.Length() > 0.0f) {		
		 return speedVec*=-0.02;
	}
	else
		return Vector3::Zero;
}
void Player::Move()
{
	if (GetPlayerNum() == 0) {
		SetAccele({ g_pad[0]->GetLStickXF() * -0.4f,0,0 });
		SetAccele({ 0,0,g_pad[0]->GetLStickYF() * -0.4f });		
		Debug();
	}
	else if (GetPlayerNum() == 1) {
		SetAccele({ g_pad[1]->GetLStickXF() * -0.4f,0,0 });
		SetAccele({ 0,0,g_pad[1]->GetLStickYF() * -0.4f });
	}	
	SetMoveSpeed(GetAccele());
	SetMoveSpeed(Decele(GetMoveSpeed()));
	m_skinModelRender->SetPosition(GetMoveSpeed());
}
void Player::Debug()
{	
	m_PosX_font->SetPosition({ 500,100 });	
	m_PosX_font->SetText(std::to_wstring(int(m_skinModelRender->GetPositionX())));
	m_PosZ_font->SetPosition({ 500,0 });
	m_PosZ_font->SetText(std::to_wstring(int(m_skinModelRender->GetPositionZ())));
}