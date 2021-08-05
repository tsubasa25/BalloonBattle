#pragma once
#include<vector>
namespace nsBalloon {
	class BalloonAir;
	class BackGround;
	class UIDisplay;
	class ResultScene;
	class GameScene;


	namespace nsPlConstant
	{
		const int MASS_DIVISOR = 20;//���D�̑傫�����玿�ʂ��o���Ƃ��̊���l
		const float REBOUND_POWER = 1.5;//�G�ƏՓ˂����Ƃ��A�����ɂ�����l
		const int INI_AIR_VOLUME = 150;//���D�̋�C�̗ʂ̏����l
		const float BALLOON_SIZE_BASE = 100;	//���D�̑傫���̊�{�l
		const Vector3 POINTLIGHT_COLOR = { 10,10,10 };//�|�C���g���C�g�̐F
		const int POINTLIGHT_RANGE = 200;//�|�C���g���C�g�̉e���͈�
		const int DESELE_VOLUME = 3500;//����������傫���𒲐�����l
		const float GRAVITY_SPEED = 0.7f;//�����X�s�[�h
		const float GRAVITY_INDEX = 2.0f;//�����X�s�[�h�ɂ�����w��
		const float PAI = 3.14159f;//�~����
		const Vector3 OVER_STAGE_LINE = { 4000.0f, -2000.0f, 4000.0f };	//�X�e�[�W���牓�����肷�������Ɏ��S���鋗���B
		const float SOUND_BALLOON_SE_VOLUME = 0.4f;
		const int RESPAWN_INTERVAL = 50;
	}
	class Player :public IGameObject
	{

	public:
		~Player();
		bool Start();
		void Update();

		void SetCanMove(bool can) { m_canMove = can; };
		bool GetCanMove() { return m_canMove; };
		/// <summary>
		/// �v���C���[�ԍ���ݒ肷��
		/// </summary>
		/// <param name="num">�v���C���[�ԍ�</param>
		void SetPlayerNum(int num) { m_playerNum = num; }
		/// <summary>
		/// �v���C���[�ԍ����擾����
		/// </summary>
		/// <returns>�v���C���[�ԍ�</returns>
		const int& GetPlayerNum() const { return m_playerNum; }

		void SetPlayerStock(int num) { m_stock = num; }
		int GetPlayerStock() { return m_stock; }//�v���C���[�̃X�g�b�N������肷��

		void SetPlayerCount(int num) { m_playerCount = num; }//�v���C���[�l����ݒ肷��

		void SetEnemyData(Player* enemy) { m_enemy.push_back(enemy); }//�G����ݒ肷��

		void SetIniPosition(Vector3 pos) { m_position = pos; m_iniPos = pos; }//�����ʒu��ݒ�
		void SetPosition(Vector3 pos) { m_skinModelRender->SetPosition(pos); m_position = pos; }
		void ReturnIniPosition() { SetPosition(m_iniPos); };

		Vector3 GetPosition() { return m_position; }

		void SetScale(Vector3 scale) { m_skinModelRender->SetScale(scale); }//�傫��
		Vector3 GetScale() { return m_skinModelRender->GetScale(); }

		Vector3 Decele(Vector3 decele);//��������

		void AddMoveSpeed(Vector3 dir) { m_moveSpeed += dir; }//�R���g���[���[���͂̒l�����Z���v����
		void SetMoveSpeed(Vector3 dir) { m_moveSpeed = dir; }//�Đݒ肷��
		Vector3 GetMoveSpeed() { return m_moveSpeed; }

		void Move();//�ړ��֐�

		void HitWall();//�ǂɂ��������Ƃ�

		void HitPlayer();//�v���C���[�ɍ������Ƃ�

		Vector3 ReboundSpeed();//���f���̖@�����甽�˂�����������߂Ĉړ����������肷��

		float GetAirVolume() { return m_myAirVolume; };
		void SetAirVolume(float air) { m_myAirVolume = air; };	//���D�̋�C�̗ʂ�ݒ�

		int GetKillPoint() { return m_killPoint; }
		void AddKillPoint() { m_killPoint++; }

		void Tilt();	//���D�̌X�������߂�B

		void PlayerDeath();	//�L�����N�^�[�����S�����Ƃ��̏���
		void BreakBalloon();	//���D�j��̏����B�����̈ʒu�Ŕj��G�t�F�N�g��\��
		void PlayEffHit();	//�v���C���[�̏Փˎ��̃G�t�F�N�g�Đ�

		void Respawn();
		void WaitRespawn() { m_respawnCount += nsPlConstant::RESPAWN_INTERVAL; };

		Vector4 GetPlColor() { return m_plColor; };

		//�f�o�b�O�p
		void Debug(int pNum);

		void SetArrowScele(Vector3 size) { m_skinModelRenderArrow->SetScale(size); };
	private:

		bool m_canMove = false;

		Vector3 m_scale = { Vector3::Zero };
		int m_playerNum = 0;//�v���C���[�ԍ�
		int m_stock = 3;//�X�g�b�N
		int m_playerCount = 0;

		Vector3 m_position = { Vector3::Zero };
		Vector3 m_iniPos = { Vector3::Zero };
		Vector3 m_resPos = { Vector3::Zero };	//���X�|�[���ʒu
		Vector3 m_decele = { Vector3::Zero };
		Vector3 m_moveSpeed = { Vector3::Zero };

		Vector3 m_lightPos = { Vector3::Zero };

		CharacterController m_charaCon;//�v���C���[�̃L�����R��

		SkinModelRender* m_skinModelRender = nullptr;

		BalloonAir* m_myAir = nullptr;

		float m_myAirVolume = nsPlConstant::INI_AIR_VOLUME;
		/// <summary>
		/// 
		/// </summary>
		Quaternion m_playerRot = { 0.0f,0.0f,0.0f,0.0f };
		std::vector<Player*> m_enemy;
		std::vector<Player*>::iterator it;
		BackGround* m_backGround = nullptr;
		UIDisplay* m_UIDisplay = nullptr;
		GameScene* m_gameScene = nullptr;
		Effect m_breakEff;

		ResultScene* m_resultScene = nullptr;

		Effect m_hitEff;

		bool m_respawnFlag = false;
		int m_respawnCount = 0;
		Vector4 m_plColor = { 0.0f,0.0f,0.0f,1.0f };

		int m_hitLastNum = 99;//�Ō�ɂ��������G�̔ԍ�
		int m_killPoint = 0;

		//�f�o�b�O�p

		int m_oldStock = m_stock;
		bool m_isArrowOn = true;//����\�����邩
		bool m_isAIOn = false;//�G�������߂����ēːi���Ă���
		SkinModelRender* m_skinModelRenderArrow = nullptr;

		Quaternion m_rot = Quaternion::Identity;
		Vector3 m_arrowSize = Vector3::One;
		Vector3 m_oldPos = Vector3::Zero;
	};
}

