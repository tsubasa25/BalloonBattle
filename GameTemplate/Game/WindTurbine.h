#pragma once
namespace nsBalloon {
	class GameScene;
	namespace nsWTConstant
	{
		const int WT_NOT_MOVE_INTERVAL = 400;	//���Ԃ������Ă��Ȃ�����
		const int WT_MOVE_INTERVAL = 250;		//���Ԃ������Ă��鎞��
	}
	class WindTurbine :public IGameObject
	{
	public:
		~WindTurbine();
		bool Start();
		void Update();
		void BladesSpin();

		void SetPosition(Vector3 pos) { m_position = pos; }
		void SetWTBledesPos(Vector3 pos) { m_WTBladesPos = pos; }
	private:
		FontRender* m_font;

		Quaternion m_rot = { 0.0f,0.0f,0.0f, 0.0f };
		Quaternion m_rotY = { 0.0f,1.0f,0.0f, 0.0f };
		Quaternion m_rotZ = { 0.0f,0.0f,0.0f, 0.0f };
		SkinModelRender* m_WTBaseModelRender = nullptr;//�x��
		SkinModelRender* m_WTBladesModelRender = nullptr;//�u���[�h
		PhysicsStaticObject m_physicsStaticObject;				//CharaCon�Ƃ̓����蔻��Ɏg�p����ÓI�����I�u�W�F�N�g

		Vector3 m_position = { Vector3::Zero };//�ʒu


		float m_angle = 0.0f;//Y���̉�]�p�x
		Vector3 m_frontY = { 0.0f,0.0f, -1.0f };//�O�������Ă������
		Vector3 m_frontZ = { 0.0f,0.0f, 0.0f };
		//Vector3 m_front = { 0.0f,0.0f, 0.0f };
		float a = 0.0f;
		float b = 0.0f;
		Vector3 m_diff;//�v���C���[�Ƃ̋���

		Vector3 m_WTBladesPos = { 0.0f, 0.0f, 0.0f };//�u���[�h�̈ʒu
		int WTMoveTimer = 0;//���[�v�J�E���g
		bool WTMoveFlag = false;//���Ԃ��������ǂ���
		Quaternion m_bladesRot = { 0.0f,0.0f,1.0f, 0.0f };//X���̉�]��Y���̉�]
		float m_bladesSpinPower = 0.01f;//��]�X�s�[�h
		float m_WTBladesAngle = 0.0f;//
		Effect eff;

		GameScene* m_gameScene = nullptr;
	};
}