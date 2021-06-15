#include "stdafx.h"
#include "Player.h"
Player::~Player()
{
	DeleteGO(m_skinModelRender);
	DeleteGO(m_enemy[3]);
}
bool Player::Start()
{
	m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->Init("Assets/modelData/unityChan.tkm");
	if (GetPlayerNum() == 0) {
		m_skinModelRender->Init("Assets/modelData/Balloon0.tkm");		
	}
	else if (GetPlayerNum() == 1) {
		m_skinModelRender->Init("Assets/modelData/Balloon1.tkm");
	}
	else if (GetPlayerNum() == 2) {
		m_skinModelRender->Init("Assets/modelData/Balloon2.tkm");
	}
	else if (GetPlayerNum() == 3) {
		m_skinModelRender->Init("Assets/modelData/Balloon3.tkm");
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

Vector3 Player::Decele(Vector3 speed)//����
{
	Vector3 speedVec = speed;
	
	if (speed.Length() > 0.0f) {		
		 return speedVec*-0.05;
	}
	else
		return Vector3::Zero;
}
void Player::Move()//�ړ�
{	
	SetMoveDirX({ g_pad[GetPlayerNum()]->GetLStickXF() * -1.1f });//�Q�[���p�b�h�œ��͂����l�����Z���ē����
	SetMoveDirZ({ g_pad[GetPlayerNum()]->GetLStickYF() * -1.1f });
	
	SetMoveDir(Decele(GetMoveDir()));//MoveDir�̏����������t�x�N�g����������(��������)
	SetAccele(GetMoveDir());//�Q�[���p�b�h�œ��͂����l�ƌ��������̒l�����Z���v����	
	
	SetPosition(GetAccele());
}

void Player::HitWall()//�ǂɂ��������Ƃ�
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
	for (int i = 0; i < 3; i++)
	{
		Vector3 diff = GetPosition() - m_enemy[i]->GetPosition();
		
		if (diff.Length() < 70) {

			Vector3 tmp = GetMoveDir();
			ResetMoveDir(m_enemy[i]->GetMoveDir());
			m_enemy[i]->ResetMoveDir(tmp);
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