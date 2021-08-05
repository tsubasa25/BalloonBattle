#pragma once
namespace nsBalloon {
	namespace nsSSConstant
	{
		const Vector3 BUIL_BALL_POS = { 200.f,50.f,0.f };//�r���p���D�̈ʒu
		const Vector3 SKY_BALL_POS = { 500,50,0 };//�󓇗p���D�̈ʒu
		const Vector3 TRAP_BALL_POS = { 200,-200,0 };//�g���b�v�p���D�̈ʒu	
		const Vector3 RANDAM_BALL_POS{ 500,-200,0 };//�����_�����D�p�̈ʒu
		const Vector3 P1_POS = { -550,100,0 };//P1�p���D�̈ʒu
		const Vector3 P2_POS = { -410,100,0 };//P2�p���D�̈ʒu
		const Vector3 P3_POS = { -270,100,0 };//P3�p���D�̈ʒu
		const Vector3 P4_POS = { -130,100,0 };//P4�p���D�̈ʒu
		const Vector3 P5_POS = { -550,-80,0 };//P5�p���D�̈ʒu
		const Vector3 P6_POS = { -410,-80,0 };//P6�p���D�̈ʒu
		const Vector3 P7_POS = { -270,-80,0 };//P7�p���D�̈ʒu
		const Vector3 P8_POS = { -130,-80,0 };//P8�p���D�̈ʒu

		const float SOUND_SELECT_BGM_VOLUME = 0.2f;//�Z���N�g��ʗpBGM�̉���
		const float SOUND_SELECT_SE_VOLUME = 0.6f;//�I�����̉���
	}
	class SelectScene :public IGameObject
	{
	public:
		bool Start();
		void Update();
		~SelectScene();
		/// <summary>
		/// �v���C���[�l����I��
		/// </summary>
		void SelectionPlayerCount();
		/// <summary>
		/// �X�g�b�N����I��
		/// </summary>
		void SelectionStockNumber();
		/// <summary>
		/// �X�e�[�W��I��
		/// </summary>
		void SelectionStage();
	private:
		/// <summary>
		/// �v���C���[�l���摜
		/// </summary>
		SpriteRender* m_cPlayerCount_Sprite;
		/// <summary>
		/// �X�g�b�N���摜
		/// </summary>
		SpriteRender* m_cStockNum_Sprite;
		/// <summary>
		/// �v���C���[��OK�摜
		/// </summary>
		SpriteRender* m_okPlayer_Sprite;
		/// <summary>
		/// �X�g�b�N��OK�摜
		/// </summary>
		SpriteRender* m_okStok_Sprite;
		/// <summary>
		/// �v���C���[��<<>>�摜
		/// </summary>
		SpriteRender* m_arrowPlayer_Sprite;
		/// <summary>
		/// �X�g�b�N����<<>>�摜
		/// </summary>
		SpriteRender* m_arrowStock_Sprite;
		/// <summary>
		/// �_�����u�v���C���[�v
		/// </summary>
		SpriteRender* m_cPlayer_Sprite;//
		/// <summary>
		/// �_�����u�X�g�b�N�v
		/// </summary>
		SpriteRender* m_cStock_Sprite;
		/// <summary>
		/// �_�����u�X�e�[�W�v
		/// </summary>
		SpriteRender* m_cStage_Sprite;
		/// <summary>
		/// �X�e�[�W�摜
		/// </summary>
		SpriteRender* m_stageBalloon_Sprite[4] = { nullptr,nullptr,nullptr,nullptr };//�󓇁A�r���A�g���b�v�A���܂���	
		/// <summary>
		/// �v���C���[�̕��D�摜
		/// </summary>
		SpriteRender* m_playerUI_Sprite[PLAYER_MAX_COUNT] = { nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr };
		/// <summary>
		/// �_�����u�X�g�b�N�v�̈ʒu
		/// </summary>
		Vector3 m_cPlayerPos = { -350,250,0 };
		/// <summary>
		/// �_�����u�X�g�b�N�v�̈ʒu
		/// </summary>
		Vector3 m_cStockPos = { -350,-250,0 };
		/// <summary>
		/// �_�����u�X�e�[�W�v�̈ʒu
		/// </summary>
		Vector3 m_StagePos = { 350,250,0 };
		/// <summary>
		/// �v���C���[�l���摜�̈ʒu
		/// </summary>
		Vector3 m_cPlayerNumPos = { 0,250,0 };
		/// <summary>
		/// �X�g�b�N���摜�̈ʒu
		/// </summary>
		Vector3 m_cStockNumPos = { 0,-250,0 };
		/// <summary>
		/// �v���C���[�l���p�s�t�摜�̈ʒu
		/// </summary>
		Vector3 m_arrowPlayerPos = { 0,250,0 };
		/// <summary>
		/// �X�g�b�N���p�s�t�摜�̈ʒu
		/// </summary>
		Vector3 m_arrowStockPos = { 0,-250,0 };
		/// <summary>
		/// �v���C���[�l���pOK!�摜�̈ʒu
		/// </summary>
		Vector3 m_okPlayerPos = { 0,250,0 };
		/// <summary>
		/// �X�g�b�N���pOK!�摜�̈ʒu
		/// </summary>
		Vector3 m_okStockPos = { 0,-250,0 };
		/// <summary>
		/// �X�e�[�W�\���p���D�摜�̈ʒu
		/// </summary>
		Vector3 m_stageBalloonPos[4] = { {nsSSConstant::SKY_BALL_POS},{nsSSConstant::BUIL_BALL_POS},{nsSSConstant::TRAP_BALL_POS},{nsSSConstant::RANDAM_BALL_POS} };
		/// <summary>
		/// �v���C���[���D�摜�̈ʒu
		/// </summary>
		Vector3 m_playerUIPos[PLAYER_MAX_COUNT] = { { nsSSConstant::P1_POS },{ nsSSConstant::P2_POS },{ nsSSConstant::P3_POS },{ nsSSConstant::P4_POS },{ nsSSConstant::P5_POS },{nsSSConstant::P6_POS },{ nsSSConstant::P7_POS },{ nsSSConstant::P8_POS } };
		/// <summary>
		/// �Z���N�g��ʗp��BGM
		/// </summary>
		SoundSource* m_selectBGM = nullptr;
		/// <summary>
		/// �I������SE
		/// </summary>
		SoundSource* m_selectSE = nullptr;
		/// <summary>
		/// �L�����Z������SE
		/// </summary>
		SoundSource* m_cancelSE = nullptr;
		/// <summary>
		/// �^�C�g���ɖ߂�܂����H�p�̉摜
		/// </summary>
		FontRender* m_titleBackFont = nullptr;
		/// <summary>
		/// �^�C�g���̏��
		/// </summary>
		enum TitleState
		{
			enBackTitle,	//�^�C�g���֖߂邩�I������B
			enPlayerNum,//�v���C���[�l���I�����
			enPlayerStock,//�v���C���[�X�g�b�N�I�����
			enStageSelect//�X�e�[�W�I�����
		};
		/// <summary>
		/// ���݂̃^�C�g���̏��
		/// </summary>
		TitleState m_titleState = enPlayerNum;
		/// <summary>
		/// �v���C���[�l��
		/// </summary>
		int m_playerCount = 2;
		/// <summary>
		/// �v���C���[�̃X�g�b�N
		/// </summary>
		int m_playerStock = 3;
		/// <summary>
		/// �X�e�[�W�̑I��ԍ�
		/// </summary>
		bool m_selectNum[2][2] = { {0,0},{0,0} };
		/// <summary>
		/// �X�e�[�W�I��ԍ���X��
		/// </summary>
		int m_XNum = 0;
		/// <summary>
		/// �X�e�[�W�I��ԍ���Y��
		/// </summary>
		int m_YNum = 0;
		/// <summary>
		/// �Z���N�g��ʂ̃��[�v�J�E���g
		/// </summary>
		float m_selectLoopCount = 0;
		/// <summary>
		/// �X�e�[�W�ԍ�0:��,1:�r��,2:�g���b�v,3:���܂���
		/// </summary>
		int m_stageNum = 0;
		/// <summary>
		/// ���_�ŗp���[�v�J�E���g
		/// </summary>
		int m_arrowLoopCount = 0;
		/// <summary>
		/// ����_�ł����邩
		/// </summary>
		bool m_arrowFlag = false;
		/// <summary>
		/// ��󂪓_�ł��鎞��
		/// </summary>
		int m_arrowSwichTime = 20;



	};
}