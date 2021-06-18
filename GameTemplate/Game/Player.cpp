#include "stdafx.h"
#include "Player.h"
#include "GameScene.h"
Player::~Player()
{
	DeleteGO(m_skinModelRender);
	DeleteGO(m_PosX_font);
	DeleteGO(m_PosY_font);
	DeleteGO(m_PosZ_font);
	DeleteGO(m_Size_font);
	DeleteGO(pointLight);
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
	if (GetPlayerNum() == 4) {
		m_skinModelRender->Init("Assets/modelData/Balloon0.tkm");
	}
	else if (GetPlayerNum() == 5) {
		m_skinModelRender->Init("Assets/modelData/Balloon1.tkm");
	}
	else if (GetPlayerNum() == 6) {
		m_skinModelRender->Init("Assets/modelData/Balloon2.tkm");
	}
	else if (GetPlayerNum() == 7) {
		m_skinModelRender->Init("Assets/modelData/Balloon3.tkm");
	}
	//�L�����R���̏�����
	m_charaCon.Init((m_bulloonSize/2) , m_bulloonSize, m_position);
	//m_charaCon.Init(100, m_bulloonSize, m_position);
	pointLight->SetColor({ 10,10,10 });
	pointLight->SetRange(200);
	pointLight->SetPosition({ m_position });
	return true;
}
void Player::Update()
{
	Move();
	HitWall();
	//HitPlayer();
	Debug(GetPlayerNum());
	SetScale({ m_bulloonSize / INI_BULLOON_SIZE,m_bulloonSize / INI_BULLOON_SIZE,m_bulloonSize / INI_BULLOON_SIZE, });	
}

Vector3 Player::Decele(Vector3 speed)//����
{
	Vector3 speedVec = speed;
	
	if (speed.Length() > 0.0f) {		
		 return speedVec*-0.02;
	}
	else {
		return Vector3::Zero;
	}
}
void Player::Move()//�ړ�
{	
	m_moveSpeed.x += g_pad[GetPlayerNum()]->GetLStickXF() * 0.5f;//�Q�[���p�b�h�œ��͂����l�����Z���ē����
	m_moveSpeed.z += g_pad[GetPlayerNum()]->GetLStickYF() * 0.5f;
	
	m_moveSpeed += Decele(m_moveSpeed);//MoveDir�̏����������t�x�N�g����������(��������)
	m_position = m_charaCon.Execute(m_moveSpeed, 1.0f);//�|�W�V����������
	if (m_charaCon.IsOnGround() == false) {//�n�ʂɂ��Ă��Ȃ�������
		m_moveSpeed.y -= pow(2,0.5f);//�d�͂�^����
	}
	else {
		m_moveSpeed.y = 0;
	}
	if (m_moveSpeed.y < -50) {//�X�e�[�W���痎������
		m_stock--;//�X�g�b�N�����炷
		if (m_stock > 0) {//�X�g�b�N���c���Ă�����
			m_moveSpeed = (m_iniPos - m_position);//�������W�ɂƂ΂�
			m_position = m_charaCon.Execute(m_moveSpeed, 1.0f);
			
			m_moveSpeed = { Vector3::Zero };//�X�s�[�h���[���ɂ���
		}
		else {
			for (int i = 0; i < m_enemy.size();i++) {
				it = std::find(
					m_enemy[i]->m_enemy.begin(),
					m_enemy[i]->m_enemy.end(),
					this
				);
				if (it != m_enemy[i]->m_enemy.end()) {
					//���������̂ō폜
					m_enemy[i]->m_enemy.erase(it);
				}
			}
			DeleteGO(this);
		}
	}
	
	SetPosition(m_position);//�ʒu��ݒ肷��
	pointLight->SetPosition({ m_position });
}

void Player::HitWall()//�ǂɂ��������Ƃ�
{			
	if (m_charaCon.GetIsHitWall() == true) {
		HitPlayer();
		if (m_enemyHit == false) {//�G�ł͂Ȃ��ǂɂ����Ă����
			//���˂�����������߂�
			m_moveSpeed = ReboundSpeed();
		}
	}
}

void Player::HitPlayer()
{
	for (int i = 0; i < m_enemy.size(); i++)		//�ǂ̓G�ɂ����������T��
	{
		Vector3 diff = GetPosition() - m_enemy[i]->GetPosition();//�G�Ƃ̋����𑪂�
		diff.y = 0;									//�����𖳎�����
		if (diff.Length() < (m_bulloonSize/2+m_enemy[i]->m_bulloonSize/2)+1) {		//�������߂����
			m_enemyHit = true;						//�G�Ƃ��������Ƃ݂Ȃ�
			Vector3 tmp = m_enemy[i]->GetMoveSpeed();//�G�̐�����ۑ�����
			m_enemy[i]->m_moveSpeed = (ReboundSpeed() * -2);//����Ɏ����̐�����n��
			
			if (m_moveSpeed.Length() < m_enemy[i]->m_mass) {//�����̐������A����̎��ʂ��傫����Β��˕Ԃ����
				m_moveSpeed = ReboundSpeed();//�����͒��˕Ԃ����
				m_enemy[i]->m_moveSpeed *= 1 / m_enemy[i]->m_mass;//�G�͂������������
			}
			else {
				//m_moveSpeed *= 1 / m_enemy[i]->m_mass;
				m_moveSpeed = tmp * 2;
			}
		}	
		else {//�G�Ƃ̋�����������΂Ȃɂ����Ȃ�
			m_enemyHit = false;						//�G�ƍ����Ă��Ȃ�
		}
	}
}

Vector3 Player::ReboundSpeed()//���f���̖@�����甽�˂�����������߂Ĉړ����������肷��
{
	//�ǂ̖@���̊O�ς����
	Vector3 wallNormal = m_charaCon.GetWallNormal();//���������ǂ̖@�����󂯎��

	Vector3 hitNormalCross = Vector3::Zero;
	hitNormalCross.Cross(Vector3::AxisY, wallNormal);//�ǂ̖@���̊O�ς����߂�

	hitNormalCross.Normalize();//���K������

	Vector3 Dir = m_moveSpeed;
	Dir.Normalize();
	//�@���̊O�ςƐi�s�����̓��ς����
	float naisei = hitNormalCross.Dot(Dir);

	Quaternion rot;
	rot.SetRotation(Vector3::AxisY, naisei * 2);//�O�ςƐi�s�����̊p�x�̍����{������
	rot.Apply(Dir);//�i�s��������]������

	return Dir * -m_moveSpeed.Length();//�i�s�����ɔ��˂���O�̐�����������
}
void Player::Debug(int pNum)//�f�o�b�O�p
{
	if (pNum == 0) {
		m_PosX_font->SetPosition({ -500,100 });
		m_PosY_font->SetPosition({ -500,50 });
		m_PosZ_font->SetPosition({ -500,0 });
		m_Size_font->SetPosition({ -500,-50 });
	}
	else if(pNum==1){
		m_PosX_font->SetPosition({ 500,100 });
		m_PosZ_font->SetPosition({ 500,0 });
	}
	m_PosX_font->SetText(std::to_wstring(int(m_skinModelRender->GetPositionX())));
	m_PosY_font->SetText(std::to_wstring(int(m_skinModelRender->GetPositionY())));
	m_PosZ_font->SetText(std::to_wstring(int(m_skinModelRender->GetPositionZ())));
	m_Size_font->SetText(std::to_wstring(int(m_bulloonSize)));
	if (g_pad[0]->IsPress(enButtonA)) {
		m_bulloonSize += 1;	
		m_mass = m_bulloonSize / MASS_DIVISOR;
		//m_charaCon.Init((m_bulloonSize / 2), m_bulloonSize, m_position);
	}
	if (g_pad[0]->IsPress(enButtonB)) {
		m_bulloonSize -= 1;
		m_mass = m_bulloonSize / MASS_DIVISOR;
	}	
	if (m_playerNum == 0) {
		Vector3 diff=Vector3::Zero;
		diff=m_position - m_enemy[0]->m_position;
		diff.Normalize();
		m_enemy[0]->m_moveSpeed += diff*0.3;
		if (m_stock != m_oldStock) {
			m_oldStock--;
			m_enemy[0]->m_moveSpeed = (m_enemy[0]->m_iniPos - m_enemy[0]->m_position);//�������W�ɂƂ΂�
			m_enemy[0]->m_position = m_enemy[0]->m_charaCon.Execute(m_enemy[0]->m_moveSpeed, 1.0f);

			m_enemy[0]->m_moveSpeed = { Vector3::Zero };//�X�s�[�h���[���ɂ���
		}
	}
}
