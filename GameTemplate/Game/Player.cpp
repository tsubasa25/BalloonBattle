#include "stdafx.h"
#include "Player.h"
#include "GameScene.h"
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
	//�L�����R���̏�����
	m_charaCon.Init(30.0f, 70.0f, m_position);
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
		 return speedVec*-0.01;
	}
	else
		return Vector3::Zero;
}
void Player::Move()//�ړ�
{	
	m_moveDir.x += g_pad[GetPlayerNum()]->GetLStickXF() * -0.5f;//�Q�[���p�b�h�œ��͂����l�����Z���ē����
	m_moveDir.z += g_pad[GetPlayerNum()]->GetLStickYF() * -0.5f;

	m_moveDir += Decele(m_moveDir);//MoveDir�̏����������t�x�N�g����������(��������)
	m_position = m_charaCon.Execute(m_moveDir, 1.0f);
	if (m_charaCon.IsOnGround() == false) {
		m_moveDir.y -= 1;
	}
	if (m_moveDir.y < -50) {
		m_moveDir = (m_iniPos-m_position);
		m_position = m_charaCon.Execute(m_moveDir, 1.0f);
		
		m_moveDir = { Vector3::Zero };
	}
	
	//m_position += m_moveDir;//�Q�[���p�b�h�œ��͂����l�ƌ��������̒l�����Z���v����	
	
	SetPosition(m_position);//�ʒu��ݒ肷��
}

void Player::HitWall()//�ǂɂ��������Ƃ�
{	
	//X�x�N�g���̌������t�ɂ��Ĕ��˂����悤�Ɍ�����
	if (m_skinModelRender->GetPositionX() >= STAGE_WIDTH&& m_skinModelRender->GetPositionZ() <= STAGE_HOLE && m_skinModelRender->GetPositionZ() >= -STAGE_HOLE)//�E�̕ǂɂ��������Ƃ�
	{}
	else if (m_skinModelRender->GetPositionX() >= STAGE_WIDTH) {
		m_position.x = STAGE_WIDTH;
		m_moveDir.x *= -1;
	}
	if (m_skinModelRender->GetPositionX() <= -STAGE_WIDTH && m_skinModelRender->GetPositionZ() <= STAGE_HOLE && m_skinModelRender->GetPositionZ() >= -STAGE_HOLE)//���̕ǂɂ��������Ƃ�
	{}			
	else if (m_skinModelRender->GetPositionX() <= -STAGE_WIDTH) {
		m_position.x = -STAGE_WIDTH;
		m_moveDir.x *= -1;
	}
	//Z�x�N�g���̌������t�ɂ��Ĕ��˂����悤�Ɍ�����
	if (m_skinModelRender->GetPositionZ() >= STAGE_DEPTH && m_skinModelRender->GetPositionX() <= STAGE_HOLE && m_skinModelRender->GetPositionX() >= -STAGE_HOLE)//
	{
		
	}
	else if (m_skinModelRender->GetPositionZ() >= STAGE_DEPTH)//���̕ǂɂ��������Ƃ�
	{
		m_position.z = STAGE_DEPTH;		
		m_moveDir.z *= -1;
	}
	if (m_skinModelRender->GetPositionZ() <= -STAGE_DEPTH && m_skinModelRender->GetPositionX() <= STAGE_HOLE && m_skinModelRender->GetPositionX() >= -STAGE_HOLE)//
	{
	}
	else if (m_skinModelRender->GetPositionZ() <= -STAGE_DEPTH)//��O�̕ǂɂ��������Ƃ�
	{
		m_position.z = -STAGE_DEPTH;		
		m_moveDir.z *= -1;
	}	
}

void Player::HitPlayer()
{	
	for (int i = 0; i < 3; i++)
	{
		Vector3 diff = GetPosition() - m_enemy[i]->GetPosition();//�G�Ƃ̋����𑪂�		
		if (diff.Length() < 70) {//�������߂����
			Vector3 tmp = GetMoveDir();			//����Ǝ����̃x�N�g������������
			ResetMoveDir(m_enemy[i]->GetMoveDir());
			m_enemy[i]->ResetMoveDir(tmp);
		}		
	}	
}
void Player::Debug(int pNum)//�f�o�b�O�p
{
	if (pNum == 0) {
		m_PosX_font->SetPosition({ -500,100 });
		m_PosY_font->SetPosition({ -500,50 });
		m_PosZ_font->SetPosition({ -500,0 });
	}
	else if(pNum==1){
		m_PosX_font->SetPosition({ 500,100 });
		m_PosZ_font->SetPosition({ 500,0 });
	}
	m_PosX_font->SetText(std::to_wstring(int(m_skinModelRender->GetPositionX())));
	m_PosY_font->SetText(std::to_wstring(int(m_skinModelRender->GetPositionY())));
	m_PosZ_font->SetText(std::to_wstring(int(m_skinModelRender->GetPositionZ())));
	if (g_pad[0]->IsPress(enButtonA)) {
		m_skinModelRender->SetPositionX(0);
		m_skinModelRender->SetPositionZ(0);
	}
}