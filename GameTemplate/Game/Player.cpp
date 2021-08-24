#include "stdafx.h"
#include "Player.h"
#include "GameScene.h"
#include "BackGround.h"
#include "UIDisplay.h"
#include "ResultScene.h"
#include "BalloonAir.h"

namespace nsBalloon {
	Player::~Player()
	{
		DeleteGO(m_skinModelRender);

		if (m_isArrowOn) {
			DeleteGO(m_skinModelRenderArrow);
		}
		DeleteGO(m_myAir);
	}
	bool Player::Start()
	{
		//�f�o�b�O�p
		m_skinModelRenderArrow = NewGO<SkinModelRender>(0);
		m_skinModelRenderArrow->SetShadowCasterFlag(false);

		m_skinModelRenderArrow->Init("Assets/modelData/arrow.tkm");
		m_skinModelRenderArrow->SetScale({ Vector3::Zero });

		m_skinModelRender = NewGO<SkinModelRender>(0);
		m_skinModelRender->SetShadowCasterFlag(true);

		//m_skinModelRender->Init("Assets/modelData/Balloon0.tkm");
		char filePath[256];
		sprintf(filePath, "Assets/modelData/Balloon%d.tkm", GetPlayerNum());
		m_skinModelRender->Init(filePath);//���D�����ꂼ��̐F�ɂ���

		m_myAir = NewGO<BalloonAir>(0, "balloonAir");
		m_myAir->SetParent(this);
		m_myAir->SetParentNum(m_playerNum);

		m_myAir->SetAirVolume(m_myAirVolume);	//��C�̗ʂ̏����l��ݒ�

		m_backGround = FindGO<BackGround>("backGround");
		m_UIDisplay = FindGO<UIDisplay>("UIdisplay");
		m_gameScene = FindGO<GameScene>("gameScene");

		//�L�����R���̏�����
		m_charaCon.Init((m_myAirVolume / 2), m_position);

		//todo char16_t�ł�sprntf�𗘗p���āB 
		//16_t�ł��Ȃ��I�H
		if (GetPlayerNum() == 0) {
			m_breakEff.Init(u"Assets/effect/BalloonBreak00.efk");
			m_plColor = { Vector4::Red };
		}
		else if (GetPlayerNum() == 1) {
			m_breakEff.Init(u"Assets/effect/BalloonBreak01.efk");
			m_plColor = { Vector4::Blue };
		}
		else if (GetPlayerNum() == 2) {
			m_breakEff.Init(u"Assets/effect/BalloonBreak02.efk");
			m_plColor = { Vector4::Green };
		}
		else if (GetPlayerNum() == 3) {
			m_breakEff.Init(u"Assets/effect/BalloonBreak03.efk");
			m_plColor = { Vector4::Yellow };
		}
		else if (GetPlayerNum() == 4) {
			m_breakEff.Init(u"Assets/effect/BalloonBreak04.efk");
			m_plColor = { Vector4::Orange };
		}
		else if (GetPlayerNum() == 5) {
			m_breakEff.Init(u"Assets/effect/BalloonBreak05.efk");
			m_plColor = { Vector4::Pink };
		}
		else if (GetPlayerNum() == 6) {
			m_breakEff.Init(u"Assets/effect/BalloonBreak06.efk");
			m_plColor = { Vector4::Gray };
		}
		else if (GetPlayerNum() == 7) {
			m_breakEff.Init(u"Assets/effect/BalloonBreak07.efk");
			m_plColor = { Vector4::Purple };
		}

		SetPosition(m_position);//�ʒu��ݒ肷��
		SetScale({ m_myAirVolume / nsPlConstant::BALLOON_SIZE_BASE,m_myAirVolume / nsPlConstant::BALLOON_SIZE_BASE,m_myAirVolume / nsPlConstant::BALLOON_SIZE_BASE, });

		m_hitEff.Init(u"Assets/effect/HitEff.efk");

		return true;
	}
	void Player::Update()
	{
		if (m_canMove == false)
		{
			if (m_respawnFlag == true)
			{
				Respawn();
			}
			return;
		}
		Move();
		Tilt();
		HitWall();
		HitPlayer();
		Debug(GetPlayerNum());
		SetScale({ m_myAirVolume / nsPlConstant::BALLOON_SIZE_BASE,m_myAirVolume / nsPlConstant::BALLOON_SIZE_BASE,m_myAirVolume / nsPlConstant::BALLOON_SIZE_BASE, });
		m_charaCon.ReInit((m_myAirVolume / 2), m_position);

		if (m_enemy.empty())
		{
			m_gameScene->SetGameState(nsGSConstant::GAME_STATE_RESULT);
			m_resultScene = NewGO<ResultScene>(0, "resultScene");
			m_resultScene->SetResultMode(m_resultScene->GetEnGameSet());
			m_resultScene->SetWinner(this);
			m_canMove = false;
		}
	}

	Vector3 Player::Decele(Vector3 speed)//����
	{
		if (speed.LengthSq() > 0.0f) {
			float SizeCoefficient = (m_myAirVolume / nsPlConstant::INI_AIR_VOLUME);//�傫���W��			
			//return speed * -m_myAirVolume / 2 / nsPlConstant::DESELE_VOLUME;
			return (speed / nsPlConstant::DESELE_VOLUME)*-SizeCoefficient;
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
			m_moveSpeed.y -= pow(nsPlConstant::GRAVITY_SPEED, nsPlConstant::GRAVITY_INDEX);//�d�͂�^����
		}
		else {
			m_moveSpeed.y = 0;
		}
		if (m_position.y < nsPlConstant::OVER_STAGE_LINE.y	//�X�e�[�W���痎���邩�A
			|| fabsf(m_position.x) > nsPlConstant::OVER_STAGE_LINE.x
			|| fabsf(m_position.z) > nsPlConstant::OVER_STAGE_LINE.z	//�X�e�[�W����傫�����ꂽ��B
			) {
			PlayerDeath();//�v���C���[���E��
			SoundSource* ss = NewGO<SoundSource>(0);//���ʉ�
			ss->Init(L"Assets/sound/���D�������Ď��񂾉�.wav");
			ss->SetVolume(nsPlConstant::SOUND_BALLOON_SE_VOLUME);
			ss->Play(false);
		}

		//�قǂ�Ǔ����Ă��Ȃ��Ƃ��A�ړ����x��0�ɂ���B
		if (fabsf(m_moveSpeed.x) < 0.1f && fabsf(m_moveSpeed.z) < 0.1f)
		{
			m_moveSpeed.x = 0.0f;
			m_moveSpeed.z = 0.0f;
		}

		SetPosition(m_position);//�ʒu��ݒ肷��
		m_lightPos = m_position;
		m_lightPos.y += m_myAirVolume;
		//pointLight->SetPosition({ m_lightPos });
	}

	void Player::HitWall()//�ǂɂ��������Ƃ�
	{
		if (m_charaCon.GetIsHitWall() == true) {
			m_moveSpeed = ReboundSpeed();

			//SE���Đ�
			SoundSource* ss = NewGO<SoundSource>(0);
			ss->Init(L"Assets/sound/���D�̒��˂鉹.wav");
			ss->SetVolume(nsPlConstant::SOUND_BALLOON_SE_VOLUME);
			ss->Play(false);
		}
	}

	void Player::HitPlayer()
	{
		for (int i = 0; i < m_enemy.size(); i++)		//�ǂ̓G�ɂ����������T��
		{
			Vector3 diff = GetPosition() - m_enemy[i]->GetPosition();//�G�Ƃ̋����𑪂�
			if (diff.Length() < (m_myAirVolume / 2 + m_enemy[i]->m_myAirVolume / 2) + 1) {//�R���W������菭���L���͈͂ɂ����炠�������Ƃ݂Ȃ�
				//diff.y = 0;									//�����𖳎�����
				//m_hitLoopCount = 0;
				Vector3 tmp = m_enemy[i]->GetMoveSpeed();//�G�̐�����ۑ�����
				diff.Normalize();//�G�Ƃ̌������Ƃ�
				//�傫���ɔ�Ⴕ�Ăӂ��Ƃ΂��₷���Ȃ�
				m_enemy[i]->m_moveSpeed = (diff * GetMoveSpeed().Length() * -(m_myAirVolume / (nsPlConstant::INI_AIR_VOLUME / nsPlConstant::REBOUND_POWER)));//����Ɏ����̐�����n��
				m_moveSpeed = diff * (tmp.Length() * ((nsPlConstant::INI_AIR_VOLUME) / m_myAirVolume));//�����͑傫���ɔ���Ⴕ�Ăӂ��Ƃ΂���₷���Ȃ�

				m_myAir->BleedAir(m_myAirVolume * 0.1f);

				PlayEffHit();

				if (m_enemy[i]->GetPlayerNum() > m_playerNum)
				{
					//SE���Đ�
					SoundSource* ss = NewGO<SoundSource>(0);
					ss->Init(L"Assets/sound/���D�̒��˂鉹.wav");
					ss->SetVolume(nsPlConstant::SOUND_BALLOON_SE_VOLUME);
					ss->Play(false);
				}
				//�Ō�ɂ��������G�̔ԍ����L�^����
				m_hitLastNum = i;
				m_enemy[i]->m_hitLastNum = i;
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

		Quaternion rot = Quaternion::Identity;
		rot.SetRotation(Vector3::AxisY, naisei * 2);//�O�ςƐi�s�����̊p�x�̍����{������
		rot.Apply(Dir);//�i�s��������]������

		return Dir * -m_moveSpeed.Length();//�i�s�����ɔ��˂���O�̐�����������
	}
	void Player::Debug(int pNum)//�f�o�b�O�p
	{
		if (m_isAIOn) {//����\�����邩
			if (m_playerCount >= 2) {//�v���C���[����l�ȏ�Ȃ�
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
		if (m_isArrowOn) {//����\�����邩�ǂ���
			//�ړ��x�N�g������������
			Vector3 Dir = m_moveSpeed;
			Dir.y = 0.f;
			Dir.Normalize();//�傫�����ʒu�ɂ���
			float x = Dir.Dot(Vector3::AxisX);//X�����牽�x����Ă��邩������
			Dir.z *= -1.f;
			float angleX = acosf(x);//�A�[�N�R�T�C��
			if (Dir.z < 0.f) {
				angleX *= -1.f;
			}
			angleX -= 0.5f * nsPlConstant::PAI;

			m_rot.SetRotationY(angleX);//���x����Y������
			m_skinModelRenderArrow->SetRotation(m_rot);//�p�x��ݒ肷��
			Vector3 ArrowPos = m_position;
			ArrowPos.y += 50.0f;

			m_skinModelRenderArrow->SetPosition(ArrowPos);

			m_arrowSize.x = m_arrowSize.z = m_moveSpeed.Length() / 3.0f;
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
		UIDisplay* UIdisplay = FindGO<UIDisplay>("UIdisplay");
		if (UIdisplay != nullptr)
		{
			UIdisplay->SetIsDeath(true);
			//�G�������DeleteGO���ꂽ�Ƃ���m_enemy�̏��Ԃ��ς�邩�炨�������Ȃ邩��
			//if (m_hitLastNum < 8) {//�N�ɂ��������ĂȂ���������Z����Ȃ�
			//	if (m_hitLastNum < m_enemy.size())
			//	{
			//		m_enemy[m_hitLastNum]->AddKillPoint();//�L���|�C���g�����Z����
			//		m_UIDisplay->SetIsMinus(m_playerNum);
			//		m_UIDisplay->SetIsPlus(m_enemy[m_hitLastNum]->GetPlayerNum());
			//		
			//	}
			//}
			UIdisplay->SetIsMinus(m_playerNum);
		}
		Effect soulEff;
		soulEff.Init(u"Assets/effect/SoulRise.efk");
		soulEff.SetPosition(m_position);
		soulEff.SetScale({ 1.0f,1.0f,1.0f });
		soulEff.Play();
		soulEff.Update();

		m_stock--;//�X�g�b�N�����炷
		//m_UIDisplay->SetPlayerDecStock(m_playerNum);//UI�ɃX�g�b�N�����������Ƃ�`����
		m_UIDisplay->SetPlayerStock(m_stock, m_playerNum);

		m_myAir->AcceleSEStop();
		m_myAir->RiseSEStop();
		m_myAir->InflateSEStop();

		if (m_stock > 0) {//�X�g�b�N���c���Ă�����
			m_respawnFlag = true;
			m_respawnCount = nsPlConstant::RESPAWN_INTERVAL;

			m_myAirVolume = nsPlConstant::INI_AIR_VOLUME;
			m_myAir->SetAirVolume(nsPlConstant::INI_AIR_VOLUME);

			m_canMove = false;
		}
		else {
			m_UIDisplay->SetPlayerDeath(m_playerNum);//UI�Ɏ��S�������Ƃ�`����			

			for (int i = 0; i < m_enemy.size(); i++) {
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
			m_myAir->SetAirVolume(nsPlConstant::INI_AIR_VOLUME);
			DeleteGO(this);
		}
	}

	void Player::BreakBalloon()
	{
		m_breakEff.SetPosition(m_position);
		//�G�t�F�N�g�̃T�C�Y�𕗑D�̃T�C�Y�ɍ��킹��B
		Vector3 size = { m_myAirVolume / nsPlConstant::BALLOON_SIZE_BASE,m_myAirVolume / nsPlConstant::BALLOON_SIZE_BASE,m_myAirVolume / nsPlConstant::BALLOON_SIZE_BASE, };
		size *= 20.0f;	//�G�t�F�N�g�̃T�C�Y��傫������B
		m_breakEff.SetScale(size);
		m_breakEff.Play();
		m_breakEff.Update();
	}

	//�Փˎ��̃G�t�F�N�g���Đ�����
	void Player::PlayEffHit()
	{
		//�G�t�F�N�g�̌������v�Z
		Vector3 front = m_moveSpeed;
		front.Normalize();
		float n = front.Dot(Vector3::AxisZ);
		float angle = acosf(n);
		if (front.z < 0) {
			angle *= -1;
		}
		Quaternion qRot = Quaternion::Identity;
		qRot.SetRotation(Vector3::AxisY, angle);
		m_hitEff.SetRotation(qRot);

		//�G�t�F�N�g�̈ʒu���v�Z
		Vector3 pos = m_position;
		pos += front * 3.0f;
		pos.y += 20.0f;
		m_hitEff.SetPosition(pos);

		//�G�t�F�N�g�̃T�C�Y
		m_hitEff.SetScale({ m_myAirVolume / 3,m_myAirVolume / 3,m_myAirVolume / 3 });

		m_hitEff.Play();
		m_hitEff.Update();
	}

	void Player::Respawn()
	{

		if (m_respawnCount == nsPlConstant::RESPAWN_INTERVAL)
		{
			//�T�C�Y�����������Č����Ȃ�����B
			m_skinModelRender->SetScale({ Vector3::Zero });
			m_charaCon.ReInit(0.0f, m_position);
			m_skinModelRenderArrow->SetScale({ Vector3::Zero });
		}
		if (m_respawnCount == 1)
		{
			m_resPos = m_backGround->GetRespawnPosition(m_playerNum);
		}
		if (m_respawnCount <= 0)
		{
			m_moveSpeed = { Vector3::Zero };//�X�s�[�h���[���ɂ���
			m_charaCon.SetPosition(m_resPos);	//�L�����R���ɍ��W��ݒ�
			SetPosition(m_resPos);	//�������W�ɔ�΂��B

			m_myAirVolume = nsPlConstant::INI_AIR_VOLUME;
			m_myAir->SetAirVolume(nsPlConstant::INI_AIR_VOLUME);

			m_respawnFlag = false;

			if (m_gameScene->GetGameState() == nsGSConstant::GAME_STATE_BATTLE)
				m_canMove = true;
		}

		m_respawnCount--;
	}
}