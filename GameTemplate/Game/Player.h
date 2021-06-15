#pragma once
class Player:public IGameObject
{
private:
	
	Vector3 m_moveSpeed = {Vector3::Zero};
	Vector3 m_position = { Vector3::Zero };
	
	Vector3 m_scale = { Vector3::Zero };
	int m_playerNum = 0;

	FontRender* m_PosX_font = NewGO<FontRender>(0);
	FontRender* m_PosZ_font = NewGO<FontRender>(0);

	Vector3 m_accele = { Vector3::Zero };
	Vector3 m_decele = { Vector3::Zero };
	Vector3 m_moveDir = { Vector3::Zero };

	CharacterController m_charaCon;//�v���C���[�̃L�����R��

	const float m_StageWidth=700.0f;	
	const float m_StageDepth=600.0f;
	
	
	Player* m_enemy[3] = { nullptr,nullptr,nullptr };
public:		
	SkinModelRender* m_skinModelRender = nullptr;
	~Player();
	bool Start();
	void Update();

	void SetPlayerNum(int num) { m_playerNum = num; }//�v���C���[�ԍ���ݒ肷��
	int GetPlayerNum() { return m_playerNum; }//�v���C���[�ԍ�����肷��

	void SetEnemy(Player* enemy, int i) { m_enemy[i] = enemy; }

	void SetPosition(Vector3 pos) { m_skinModelRender->SetPosition(pos); }
	Vector3 GetPosition() { return m_skinModelRender->GetPosition(); }

	void SetScale(Vector3 scale) { m_scale = scale; }//�傫��
	Vector3 GetScale() { return m_scale; }

	void SetAccele(Vector3 accele) { m_accele += accele; }//�R���g���[���[������͂��ꂽ�l�����Z���v
	void SetAcceleX(float acceleX) { m_accele.x = acceleX; };
	void SetAcceleZ(float acceleZ) { m_accele.z = acceleZ; };
	Vector3 GetAccele() { return m_accele; }

	Vector3 Decele(Vector3 decele);//��������
	
	float GetStageWidth() { return m_StageWidth; }//�X�e�[�W�̉���
	float GetStageDepth() { return m_StageDepth; }//�X�e�[�W�̏c��

	void SetMoveDir(Vector3 dir) { m_moveDir += dir; }//�R���g���[���[���͂̒l�����Z���v����
	void SetMoveDirX(float dirX) { m_moveDir.x += dirX; }
	void SetMoveDirZ(float dirZ) { m_moveDir.z += dirZ; }
	void ResetMoveDir(Vector3 dir) { m_moveDir = dir; }//�Đݒ肷��
	void ResetMoveDirX(float dirX) { m_moveDir.x = dirX; }
	void ResetMoveDirZ(float dirZ) { m_moveDir.z = dirZ; }
	Vector3 GetMoveDir() { return m_moveDir; }
	float GetMoveDirX() { return m_moveDir.x; }
	float GetMoveDirZ() { return m_moveDir.z; }

	void Move();//�ړ��֐�

	void HitWall();//�ǂɂ��������Ƃ�

	void HitPlayer();//�v���C���[�ɍ������Ƃ�
	
	void Debug(int pNum);//�f�o�b�O�p
};

