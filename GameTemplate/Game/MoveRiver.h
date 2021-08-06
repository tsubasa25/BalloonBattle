#pragma once
namespace nsBalloon {
	class MoveRiver :public IGameObject
	{
		bool Start()override;
		void Update()override;
		void Render(RenderContext& rc, Camera* camera);
	private:
		struct RiverData
		{
			float textureSize;//�e�N�X�`���̃T�C�Y(�����`��z�肵�Ă���̂�float�B)
			float scrollingValue = 0;//�X�N���[����
		};
		Model m_riverModel;	//��̃��f���A2��ʗp��2�p�ӂ���B
		RiverData m_riverData;		//�V�F�[�_�[�ɓn������̃f�[�^
	};

}