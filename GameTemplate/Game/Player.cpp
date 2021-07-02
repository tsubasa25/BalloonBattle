#include "stdafx.h"
#include "Player.h"
#include "GameScene.h"
#include "BackGround.h"
#include "UIDisplay.h"
Player::~Player()
{
	DeleteGO(m_skinModelRender);
	DeleteGO(m_PosX_font);
	DeleteGO(m_PosY_font);
	DeleteGO(m_PosZ_font);
	DeleteGO(m_Size_font);
	DeleteGO(pointLight);
	if (m_IsArrowOn) {
		DeleteGO(m_skinModelRenderArrow);
	}
	GameScene* gameScene = FindGO<GameScene>("gameScene");
	gameScene->SetIsAlive(m_playerNum, false);
	gameScene->SetPlayerCount(gameScene->GetPlayerCount() - 1);
	
	DeleteGO(m_myAir);
}
bool Player::Start()
{
	//�f�o�b�O�p
	m_skinModelRenderArrow = NewGO<SkinModelRender>(0);
	m_skinModelRenderArrow->Init("Assets/modelData/arrow.tkm");

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
	else if (GetPlayerNum() == 4) {
		m_skinModelRender->Init("Assets/modelData/Balloon4.tkm");
	}
	else if (GetPlayerNum() == 5) {
		m_skinModelRender->Init("Assets/modelData/Balloon5.tkm");
	}
	else if (GetPlayerNum() == 6) {
		m_skinModelRender->Init("Assets/modelData/Balloon6.tkm");
	}
	else if (GetPlayerNum() == 7) {
		m_skinModelRender->Init("Assets/modelData/Balloon7.tkm");
	}

	m_myAir = NewGO<BalloonAir>(0);
	m_myAir->SetParent(this);
	m_myAir->SetParentNum(m_playerNum);

	m_myAir->SetAirVolume(m_myAirVolume);	//��C�̗ʂ̏����l��ݒ�

	m_backGround = FindGO<BackGround>("backGround");
	m_UIDisplay = FindGO<UIDisplay>("UIdisplay");

	//�L�����R���̏�����
	m_charaCon.Init((m_myAirVolume/2), m_position);

	//m_charaCon.Init(100, m_bulloonSize, m_position);
	pointLight->SetColor(POINTLIGHT_COLOR);
	pointLight->SetRange(POINTLIGHT_RANGE);
	pointLight->SetPosition({ m_position });

	return true;
}
void Player::Update()
{
	Move();
	Tilt();
	HitWall();
	HitPlayer();
	Debug(GetPlayerNum());
	SetScale({ m_myAirVolume / BALLOON_SIZE_BASE,m_myAirVolume / BALLOON_SIZE_BASE,m_myAirVolume / BALLOON_SIZE_BASE, });
	m_charaCon.ReInit((m_myAirVolume / 2), m_position);	
}

Vector3 Player::Decele(Vector3 speed)//����
{
	Vector3 speedVec = speed;
	
	if (speed.Length() > 0.0f) {		
		//return speedVec*-0.02;
		return speedVec * -m_myAirVolume/2 / DESELE_VOLUME;
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
		m_moveSpeed.y -= pow( GRAVITY_SPEED,GRAVITY_INDEX );//�d�͂�^����
	}
	else {
		m_moveSpeed.y = 0;
	}
	if (m_position.y < OVER_STAGE_LINE.y	//�X�e�[�W���痎���邩�A
		|| fabsf(m_position.x) > OVER_STAGE_LINE.x
		|| fabsf(m_position.z) > OVER_STAGE_LINE.z	//�X�e�[�W����傫�����ꂽ��B
		) {
		PlayerDeath();
	}

	//�قǂ�Ǔ����Ă��Ȃ��Ƃ��A�ړ����x��0�ɂ���B
	if (fabsf(m_moveSpeed.x) < 0.1f && fabsf(m_moveSpeed.z) < 0.1f)
	{
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;
	}
	
	SetPosition(m_position);//�ʒu��ݒ肷��
	pointLight->SetPosition({ m_position });
}

void Player::HitWall()//�ǂɂ��������Ƃ�
{			
	if (m_charaCon.GetIsHitWall() == true) {
		m_moveSpeed = ReboundSpeed();
	}
}

void Player::HitPlayer()
{
	for (int i = 0; i < m_enemy.size(); i++)		//�ǂ̓G�ɂ����������T��
	{
		Vector3 diff = GetPosition() - m_enemy[i]->GetPosition();//�G�Ƃ̋����𑪂�
		if (diff.Length() < (m_myAirVolume /2+m_enemy[i]->m_myAirVolume /2)+1) {//�R���W������菭���L���͈͂ɂ����炠�������Ƃ݂Ȃ�
			//diff.y = 0;									//�����𖳎�����
			//m_hitLoopCount = 0;
			Vector3 tmp = m_enemy[i]->GetMoveSpeed();//�G�̐�����ۑ�����
			diff.Normalize();//�G�Ƃ̌������Ƃ�
			//�傫���ɔ�Ⴕ�Ăӂ��Ƃ΂��₷���Ȃ�
			m_enemy[i]->m_moveSpeed = (diff*GetMoveSpeed().Length() * -(m_myAirVolume/ (INI_AIR_VOLUME/ REBOUND_POWER)));//����Ɏ����̐�����n��
			m_moveSpeed = diff*(tmp.Length() * ((INI_AIR_VOLUME) /m_myAirVolume));//�����͑傫���ɔ���Ⴕ�Ăӂ��Ƃ΂���₷���Ȃ�
		
			m_myAir->BleedAir(m_myAirVolume * 0.1f);
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
	m_Size_font->SetText(std::to_wstring(int(m_myAirVolume)));	
	if (g_pad[pNum]->IsPress(enButtonLB1)) {
			m_myAirVolume += 1;
			//m_charaCon.ReInit((m_myAirVolume / 2), m_position);

			//m_charaCon.ReInit((m_myAirVolume / 2),m_position);
			//m_moveSpeed.y = 0;
	}
	if (g_pad[pNum]->IsPress(enButtonRB1)) {
			m_myAirVolume -= 1;
			Vector3 Accele = m_moveSpeed;
			Accele.Normalize();
			m_moveSpeed += Accele;
			//m_charaCon.ReInit((m_myAirVolume / 2),m_position);
	}
	
	
	if (m_playerCount >= 2) {//�v���C���[����l�ȏ�Ȃ�
		if (m_IsAIOn) {
			if (m_playerNum == 0) {//�G�������߂����ēːi���Ă���
				Vector3 diff = Vector3::Zero;
				diff = m_position - m_enemy[0]->m_position;
				diff.Normalize();
				m_enemy[0]->m_moveSpeed += diff * 0.3f;
				if (m_stock != m_oldStock) {
					m_oldStock--;
					m_enemy[0]->m_moveSpeed = (m_enemy[0]->m_iniPos - m_enemy[0]->m_position);//�������W�ɂƂ΂�
					m_enemy[0]->m_position = m_enemy[0]->m_charaCon.Execute(m_enemy[0]->m_moveSpeed, 1.0f);

					m_enemy[0]->m_moveSpeed = { Vector3::Zero };//�X�s�[�h���[���ɂ���
				}
			}
		}
	}
	if (m_IsArrowOn) {//����\�����邩�ǂ���
		//�ړ��x�N�g������������
		Vector3 Dir = m_moveSpeed;
		Dir.y = 0;
		Dir.Normalize();//�傫�����ʒu�ɂ���
		float x = Dir.Dot(Vector3::AxisX);//X�����牽�x����Ă��邩������
		Dir.z *= -1;
		float angleX = acosf(x);//�A�[�N�R�T�C��
		if (Dir.z < 0) {
			angleX *= -1;
		}
		angleX -= 0.5 * PAI;

		m_rot.SetRotationY(angleX);//���x����Y������
		m_skinModelRenderArrow->SetRotation(m_rot);//�p�x��ݒ肷��

		m_skinModelRenderArrow->SetPosition(m_position);

		m_arrowSize.x = m_arrowSize.z = m_moveSpeed.Length() / 3;
		m_skinModelRenderArrow->SetScale(m_arrowSize);
	}
}

void Player::Tilt()
{
	Vector3 dir = m_moveSpeed;
	dir.y = 0.0f;
	dir.Normalize();

	float tiltPower = m_moveSpeed.Length() * 0.02f;

	Vector3 right = Cross(Vector3::AxisY, dir);
	
	m_playerRot.SetRotation(right, tiltPower);

	m_playerRot.Apply(dir);

	m_skinModelRender->SetRotation(m_playerRot);

}

//�v���C���[�����S�����Ƃ��̏���
void Player::PlayerDeath()
{
	m_stock--;//�X�g�b�N�����炷
	m_UIDisplay->SetPlayerDecStock(m_playerNum);//UI�ɃX�g�b�N�����������Ƃ�`����
	if (m_stock > 0) {//�X�g�b�N���c���Ă�����
		m_resPos = m_backGround->GetRespawnPosition(m_playerNum);
		m_moveSpeed = { Vector3::Zero };//�X�s�[�h���[���ɂ���
		m_charaCon.SetPosition(m_resPos);	//�L�����R���ɍ��W��ݒ�
		SetPosition(m_resPos);	//�������W�ɔ�΂��B
		
		m_myAirVolume = INI_AIR_VOLUME;
		m_myAir->SetAirVolume(INI_AIR_VOLUME);
	}
	else {			
			m_UIDisplay->SetPlayerDeath(m_playerNum);//UI�Ɏ��S�������Ƃ�`����			
		
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