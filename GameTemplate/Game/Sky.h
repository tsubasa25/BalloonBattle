#pragma once
class Sky:public IGameObject
{
public: 
	
/**
		 * @brief ���f���̏������֐��@�A�j���[�V������
		 * @param modelPath ���f���t�@�C���̃p�X(.tkm)
		 * @param skeletonPath �X�P���g���t�@�C���̃p�X(.tks)
		 * @param animClips �A�j���[�V�����N���b�v�̔z��
		 * @param animClipNum �A�j���[�V�����N���b�v�̐�
		*/
	void Init(const wchar_t* filePath);
	void Render(RenderContext& rc, Camera* camera)override;
	void Update()override;
	void SetRotation(Quaternion rot) { m_qRot = rot; }
private:
	Model m_model; //���f��
	Vector3 m_scale = { 100.0f, 100.0f, 100.0f };		//��̊g�嗦�B
	Quaternion m_qRot;
	Vector3 m_position = Vector3::Zero;					//���W�B
	Texture m_skyTexture;
	bool m_isDirty = false;									//�_�[�e�B�t���O�B
	float m_add = 0;
};

