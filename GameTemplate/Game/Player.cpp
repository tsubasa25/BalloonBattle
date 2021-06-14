#include "stdafx.h"
#include "Player.h"
Player::~Player()
{

}
bool Player::Start()
{
	m_skinModelRender = NewGO<SkinModelRender>(0);
	if (GetPlayerNum() == 0) {
		m_skinModelRender->Init("Assets/modelData/Balloon0.tkm");		
	}
	else if (GetPlayerNum() == 1) {
		m_skinModelRender->Init("Assets/modelData/Balloon1.tkm");
	}
	
	return true;
}
void Player::Update()
{
	
	Move();
	HitWall();
	HitPlayer();
	Debug(GetPlayerNum());

}

Vector3 Player::Decele(Vector3 speed)//減速
{
	Vector3 speedVec = speed;
	
	if (speed.Length() > 0.0f) {		
		 return speedVec*-0.05;
	}
	else
		return Vector3::Zero;
}
void Player::Move()//移動
{	
	SetMoveDirX({ g_pad[GetPlayerNum()]->GetLStickXF() * -1.1f });//ゲームパッドで入力した値を加算して入れる
	SetMoveDirZ({ g_pad[GetPlayerNum()]->GetLStickYF() * -1.1f });
	
	SetMoveDir(Decele(GetMoveDir()));//MoveDirの小さくした逆ベクトルを代入する(減速処理)
	SetAccele(GetMoveDir());//ゲームパッドで入力した値と減速処理の値を加算合計する	
	
	SetPosition(GetAccele());
}

void Player::HitWall()//壁にあたったとき
{	
	if (m_skinModelRender->GetPositionX() >= m_StageWidth)
	{
		SetAcceleX(GetStageWidth());
		ResetMoveDirX(GetMoveDirX() * -1.0);
		ResetMoveDirZ(GetMoveDirZ() * 1.0);

		//m_skinModelRender->SetPositionX(GetStageWidth());
	}
	if (m_skinModelRender->GetPositionX() <= -m_StageWidth)
	{
		SetAcceleX(-GetStageWidth());
		ResetMoveDirX(GetMoveDirX() * -1.0);
		ResetMoveDirZ(GetMoveDirZ() * 1.0);
		
		//m_skinModelRender->SetPositionX(-GetStageWidth());
	}

	if (m_skinModelRender->GetPositionZ() >= m_StageDepth)
	{
		SetAcceleZ(GetStageDepth());
		ResetMoveDirX(GetMoveDirX() * 1.0);
		ResetMoveDirZ(GetMoveDirZ() * -1.0);
		
		//m_skinModelRender->SetPositionZ(GetStageDepth());
	}
	if (m_skinModelRender->GetPositionZ() <= -m_StageDepth)
	{
		SetAcceleZ(-GetStageDepth());
		ResetMoveDirX(GetMoveDirX() * 1.0);
		ResetMoveDirZ(GetMoveDirZ() * -1.0);

		//m_skinModelRender->SetPositionZ(-GetStageDepth());
	}	
}

void Player::HitPlayer()
{	
	Vector3 diff = GetPosition() - m_enemy->GetPosition();
	if (m_playerNum == 0) {
		if (diff.Length() < 70) {

			Vector3 tmp = GetMoveDir();
			ResetMoveDir(m_enemy->GetMoveDir());
			m_enemy->ResetMoveDir(tmp);
		}
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
	if (g_pad[0]->IsPress(enButtonA)) {
		m_skinModelRender->SetPositionX(0);
		m_skinModelRender->SetPositionZ(0);
	}
}