#pragma once
#include<vector>
namespace
{
	const int STAGE_WIDTH = 750;
	const int STAGE_DEPTH = 750;	
	const int INI_BALLOON_SIZE = 70;//���D�̑傫���̏����l
	const int MAX_BALLOON_SIZE = 350;	//���D���傫���Ȃ��ő�T�C�Y
	const int MIN_BALLOON_SIZE = 10;	//���D���������Ȃ��ő�T�C�Y
	const int MASS_DIVISOR = 20;//���D�̑傫�����玿�ʂ��o���Ƃ��̊���l
	const float REBOUND_POWER = 2;//�G�ƏՓ˂����Ƃ��A�����ɂ�����l
	const float BRAKE_POWER = 0.1;	//�u���[�L���s�����ۂ�m_moveSpeed�ɂ�����l
}
class Player:public IGameObject
{
private:
	
	Vector3 m_scale = { Vector3::Zero };
	int m_playerNum = 0;//�v���C���[�ԍ�
	int m_stock = 3;//�X�g�b�N
	int m_playerCount = 0;
	FontRender* m_PosX_font = NewGO<FontRender>(0);//�f�o�b�O�p
	FontRender* m_PosY_font = NewGO<FontRender>(0);
	FontRender* m_PosZ_font = NewGO<FontRender>(0);
	FontRender* m_Size_font = NewGO<FontRender>(0);
	PointLight* pointLight = NewGO<PointLight>(0);	
	
	Vector3 m_position = { Vector3::Zero };
	Vector3 m_iniPos= { Vector3::Zero };
	Vector3 m_decele = { Vector3::Zero };
	Vector3 m_moveSpeed = { Vector3::Zero };

	CharacterController m_charaCon;//�v���C���[�̃L�����R��

	SkinModelRender* m_skinModelRender = nullptr;
	

	float m_balloonSize = INI_BALLOON_SIZE;//���D�̑傫��(��)
	bool m_enemyHit = false;//�G�Ƃ��������Ƃ�		
public:
	std::vector<Player*> m_enemy;
	std::vector<Player*>::iterator it;
	~Player();
	bool Start();
	void Update();

	void SetPlayerNum(int num) { m_playerNum = num; }//�v���C���[�ԍ���ݒ肷��
	int GetPlayerNum() { return m_playerNum; }//�v���C���[�ԍ�����肷��

	void SetPlayerCount(int num) { m_playerCount = num; }//�v���C���[�l����ݒ肷��

	void SetEnemy(Player* enemy, int i) { m_enemy[i] = enemy; }//�G����ݒ肷��

	void SetIniPosition(Vector3 pos) { m_position = pos; m_iniPos = pos; }//�����ʒu��ݒ�
	void SetPosition(Vector3 pos) { m_skinModelRender->SetPosition(pos); m_position = pos; }
	Vector3 GetPosition() { return m_position; }

	void SetScale(Vector3 scale) { m_skinModelRender->SetScale(scale); }//�傫��
	Vector3 GetScale() { return m_skinModelRender->GetScale(); }

	Vector3 Decele(Vector3 decele);//��������
	
	float GetStageWidth() { return STAGE_WIDTH; }//�X�e�[�W�̉���
	float GetStageDepth() { return STAGE_DEPTH; }//�X�e�[�W�̏c��

	void SetMoveSpeed(Vector3 dir) { m_moveSpeed += dir; }//�R���g���[���[���͂̒l�����Z���v����
	void ResetMoveSpeed(Vector3 dir) { m_moveSpeed = dir; }//�Đݒ肷��
	Vector3 GetMoveSpeed() { return m_moveSpeed; }
	
	void Move();//�ړ��֐�

	void HitWall();//�ǂɂ��������Ƃ�

	void HitPlayer();//�v���C���[�ɍ������Ƃ�
	
	Vector3 ReboundSpeed();//���f���̖@�����甽�˂�����������߂Ĉړ����������肷��

	void Air();	//���D�̋�C�Ɋւ���֐�

	void AddAir(float air);		//air�̒l���A��C������
	void BleedAir(float air);	//air�̒l���A��C�𔲂�

	//�f�o�b�O�p
	void Debug(int pNum);
	int m_oldStock = m_stock;
	bool m_IsArrowOn = true;//����\�����邩
	bool m_IsAIOn = false;//�G�������߂����ēːi���Ă���
	SkinModelRender* m_skinModelRenderArrow = nullptr;
	Quaternion m_rot;
	Vector3 m_arrowSize = Vector3::One;
	Vector3 m_oldPos = Vector3::Zero;

};

