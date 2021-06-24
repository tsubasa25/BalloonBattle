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
	if (m_IsArrowOn) {
		DeleteGO(m_skinModelRenderArrow);
	}
	GameScene* gameScene = FindGO<GameScene>("gameScene");
	gameScene->SetIsAlive(m_playerNum, false);
	gameScene->SetPlayerCount(gameScene->GetPlayerCount() - 1);
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
	//�L�����R���̏�����
	m_charaCon.Init((m_balloonSize/2) , m_balloonSize, m_position);
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
	Air();
	Debug(GetPlayerNum());
	SetScale({ m_balloonSize / INI_BALLOON_SIZE,m_balloonSize / INI_BALLOON_SIZE,m_balloonSize / INI_BALLOON_SIZE, });	
}

Vector3 Player::Decele(Vector3 speed)//����
{
	Vector3 speedVec = speed;
	
	if (speed.Length() > 0.0f) {		
		 //return speedVec*-0.02;
		return speedVec * -m_balloonSize / 3500;
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
		m_moveSpeed.y -= pow(0.7f, 2.0f);//�d�͂�^����
	}
	else {
		m_moveSpeed.y = 0;
	}
	if (m_position.y < -1000) {//�X�e�[�W���痎������
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
		HitPlayer();
		if (m_enemyHit == false) {//�G�ł͂Ȃ��ǂɂ����Ă����
			//��C��������
			//BleedAir(m_moveSpeed.Length());

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
		//if (diff.Length() < (m_bulloonSize/2+m_enemy[i]->m_bulloonSize/2)+1) {//�R���W������Update�ł����炱����
		if (diff.Length() < (INI_BALLOON_SIZE+2)){//�������߂����
			m_enemyHit = true;						//�G�Ƃ��������Ƃ݂Ȃ�
			Vector3 tmp = m_enemy[i]->GetMoveSpeed();//�G�̐�����ۑ�����
			//�傫���ɔ�Ⴕ�Ăӂ��Ƃ΂��₷���Ȃ�
			m_enemy[i]->m_moveSpeed = (ReboundSpeed() * -(m_balloonSize/ (INI_BALLOON_SIZE/ REBOUND_POWER)));//����Ɏ����̐�����n��
			
			if (m_moveSpeed.Length() < m_enemy[i]->m_balloonSize / MASS_DIVISOR) {//�����̐������A����̎��ʂ��傫����Β��˕Ԃ����
				m_enemy[i]->m_moveSpeed = (ReboundSpeed() * -(m_balloonSize / (INI_BALLOON_SIZE * REBOUND_POWER)));//�G�͂������������
				m_moveSpeed = ReboundSpeed();//�����͒��˕Ԃ����				
			}
			else {				
				m_moveSpeed = tmp * ((INI_BALLOON_SIZE* REBOUND_POWER) /m_balloonSize);//�����͑傫���ɔ���Ⴕ�Ăӂ��Ƃ΂���₷���Ȃ�
			}
			//BleedAir(m_moveSpeed.Length());	//�����̋�C��������
			//m_enemy[i]->BleedAir(m_moveSpeed.Length());//����̋�C��������B
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
	m_Size_font->SetText(std::to_wstring(int(m_balloonSize)));	
	if (g_pad[pNum]->IsPress(enButtonLB1)) {
			m_balloonSize += 1;			
			//m_charaCon.ReInit((m_bulloonSize / 2), 70,m_position);
			//m_moveSpeed.y = 0;
	}
	if (g_pad[pNum]->IsPress(enButtonRB1)) {
			m_balloonSize -= 1;			
			Vector3 Accele = m_moveSpeed;
			Accele.Normalize();
			m_moveSpeed += Accele;
			//m_charaCon.ReInit((m_bulloonSize / 2), 70,m_position);
	}
	
	
	if (m_playerCount >= 2) {//�v���C���[����l�ȏ�Ȃ�
		if (m_IsAIOn) {
			if (m_playerNum == 0) {//�G�������߂����ēːi���Ă���
				Vector3 diff = Vector3::Zero;
				diff = m_position - m_enemy[0]->m_position;
				diff.Normalize();
				m_enemy[0]->m_moveSpeed += diff * 0.3;
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
		angleX -= 0.5 * 3.14159;

		m_rot.SetRotationY(angleX);//���x����Y������
		m_skinModelRenderArrow->SetRotation(m_rot);//�p�x��ݒ肷��

		m_skinModelRenderArrow->SetPosition(m_position);

		m_arrowSize.x = m_arrowSize.z = m_moveSpeed.Length() / 3;
		m_skinModelRenderArrow->SetScale(m_arrowSize);
	}
}

//���D�̋�C�֌W
void Player::Air()
{
	Vector3 speedToHorizontal = m_moveSpeed;	//���������ւ̃X�s�[�h(y������0)
	speedToHorizontal.y = 0;

	//�u���[�L�Ƌ�C�����̏���
	if (g_pad[GetPlayerNum()]->IsPress(enButtonB))
	{
		if (speedToHorizontal.Length() > 0.0f)
		{
			//�u���[�L��������B
			m_moveSpeed.x -= m_moveSpeed.x * BRAKE_POWER;
			m_moveSpeed.z -= m_moveSpeed.z * BRAKE_POWER;
			BleedAir(speedToHorizontal.Length() * BRAKE_POWER);	//�u���[�L�̃f�����b�g�Ƃ��ċ�C��������
		}
		else
		{
			//�T�C�Y��傫������B
			AddAir(1.0f);
		}
	}
	
	//�v���C���[���X�e�B�b�N��|���Ă���Ƃ�
	if (g_pad[GetPlayerNum()]->GetLStickXF() != 0.0f
		|| g_pad[GetPlayerNum()]->GetLStickYF() != 0.0f)
	{
		//L�X�e�B�b�N�̌X���̑傫���ɉ����āA��C��������B
		Vector3 LStickTilt = {
			(g_pad[GetPlayerNum()]->GetLStickXF()),
			(g_pad[GetPlayerNum()]->GetLStickYF()),
			0.0f
		};
		BleedAir(LStickTilt.Length() * 0.05f);

		//A�{�^���������ꂽ��A��C�o�[�X�g�I��C�𕬎˂��Ĉ�C�ɉ����B
		//�����̓��e�ԈႦ���B�����B
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			Vector3 boostDir;
			boostDir.x = g_pad[GetPlayerNum()]->GetLStickXF();
			boostDir.z = g_pad[GetPlayerNum()]->GetLStickYF();
			boostDir.y = 0.0f;
			boostDir.Normalize();

			boostDir.x *= 70.0f;
			boostDir.z *= 70.0f;

			m_moveSpeed.x = boostDir.x;
			m_moveSpeed.z = boostDir.z;

			//��C�����ʔ�����B
			BleedAir(20.0f);
		}
	}
	if (g_pad[0]->IsTrigger(enButtonY))
	{
		m_moveSpeed.y = 30.0f;
		//��C�����ʔ�����B
		BleedAir(20.0f);
	}
}

//air�̒l���A���D�ɋ�C��������
void Player::AddAir(float air)
{ 
	m_balloonSize += air;
	if (m_balloonSize > MAX_BALLOON_SIZE)	//�ő�T�C�Y���͑傫���Ȃ�Ȃ��B
		m_balloonSize = MAX_BALLOON_SIZE;
}
//air�̒l���A���D�̋�C�𔲂�
void  Player::BleedAir(float air)			
{ 
	m_balloonSize -= air; 
	if (m_balloonSize < MIN_BALLOON_SIZE)	//�ŏ��T�C�Y���͏������Ȃ�Ȃ��B
		m_balloonSize = MIN_BALLOON_SIZE;
}