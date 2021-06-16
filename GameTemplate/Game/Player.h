#pragma once
#include<vector>
namespace
{
	const int STAGE_WIDTH = 750;
	const int STAGE_DEPTH = 750;
	const int STAGE_HOLE = 350;
	const float INI_BULLOON_SIZE = 70;
}
class Player:public IGameObject
{
private:
	
	Vector3 m_scale = { Vector3::Zero };
	int m_playerNum = 0;//�v���C���[�ԍ�
	int m_stock = 1;//�X�g�b�N
	int m_playerCount = 4;
	FontRender* m_PosX_font = NewGO<FontRender>(0);//�f�o�b�O�p
	FontRender* m_PosY_font = NewGO<FontRender>(0);
	FontRender* m_PosZ_font = NewGO<FontRender>(0);
	FontRender* m_Size_font = NewGO<FontRender>(0);

	Vector3 m_position = { Vector3::Zero };
	Vector3 m_iniPos= { Vector3::Zero };
	Vector3 m_decele = { Vector3::Zero };
	Vector3 m_moveDir = { Vector3::Zero };

	CharacterController m_charaCon;//�v���C���[�̃L�����R��

	SkinModelRender* m_skinModelRender = nullptr;
	

	float m_bulloonSize = 70;
public:		
	std::vector<Player*> m_enemy;
	std::vector<Player*>::iterator it;
	~Player();
	bool Start();
	void Update();

	void SetPlayerNum(int num) { m_playerNum = num; }//�v���C���[�ԍ���ݒ肷��
	int GetPlayerNum() { return m_playerNum; }//�v���C���[�ԍ�����肷��

	void SetEnemy(Player* enemy, int i) { m_enemy[i] = enemy; }//�G����ݒ肷��

	void SetIniPosition(Vector3 pos) { m_position = pos; m_iniPos = pos; }//�����ʒu��ݒ�
	void SetPosition(Vector3 pos) { m_skinModelRender->SetPosition(pos); }
	Vector3 GetPosition() { return m_skinModelRender->GetPosition(); }

	void SetScale(Vector3 scale) { m_skinModelRender->SetScale(scale); }//�傫��
	Vector3 GetScale() { return m_skinModelRender->GetScale(); }

	Vector3 Decele(Vector3 decele);//��������
	
	float GetStageWidth() { return STAGE_WIDTH; }//�X�e�[�W�̉���
	float GetStageDepth() { return STAGE_DEPTH; }//�X�e�[�W�̏c��

	void SetMoveDir(Vector3 dir) { m_moveDir += dir; }//�R���g���[���[���͂̒l�����Z���v����
	void ResetMoveDir(Vector3 dir) { m_moveDir = dir; }//�Đݒ肷��
	Vector3 GetMoveDir() { return m_moveDir; }
	
	void Move();//�ړ��֐�

	void HitWall();//�ǂɂ��������Ƃ�

	void HitPlayer();//�v���C���[�ɍ������Ƃ�
	
	void Debug(int pNum);//�f�o�b�O�p
};

