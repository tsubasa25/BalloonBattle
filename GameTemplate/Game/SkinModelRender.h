#pragma once

class DirectionLight;
class PointLight;
class SpotLight;

class SkinModelRender:public IGameObject
{
public:
	SkinModelRender() :m_position(Vector3::Zero), m_qRot(g_quatIdentity), m_scale(Vector3::One) {}
	~SkinModelRender();
	void Update();
	/**
	 * @brief ���f���̏����X�V����
	*/
	void UpdateModel();

	//���C�g�̏��ƃJ�����̈ʒu
	//struct LigDatas
	//{
	//	DirLigData directionLight;
	//	PointLigData pointLight;
	//	SpotLigData spotLight;
	//	Vector3 eyePos;
	//};
	//LigDatas m_ligData;//���C�g�̃f�[�^
	//int m_size = sizeof(m_ligData);	//���C�g�̃f�[�^�̃T�C�Y

	void Render(RenderContext& rc)override;
	/**
		 * @brief ���f���̕`��
		 * @param rc �����_�[�R���e�L�X�g
		 * @param camera �`�悷��J����
		*/
	
	/**
		 * @brief ���f���̏������֐��@�A�j���[�V������
		 * @param modelPath ���f���t�@�C���̃p�X(.tkm)
		 * @param skeletonPath �X�P���g���t�@�C���̃p�X(.tks)
		 * @param animClips �A�j���[�V�����N���b�v�̔z��
		 * @param animClipNum �A�j���[�V�����N���b�v�̐�
		*/
	void Init(const char* modelPath, const char* skeletonPath, AnimationClip* animClips, int animClipNum);

	/**
		 * @brief ���f���̏������֐�
		 * @param modelPath ���f���t�@�C���̃p�X(.tkm)
		 * @param skeletonPath �X�P���g���t�@�C���̃p�X(.tks)
		*/
	void Init(const char* modelPath, const char* skeletonPath);
	/**
		 * @brief ���f���̏������֐��@���f���p�X������
		 * @param modelPath ���f���t�@�C���̃p�X(.tkm)
		*/
	void Init(const char* modelPath);
	
	/**
		 * @brief ���f���̍��W��ݒ肷��
		 * @param pos ���W
		*/
	void SetPosition(Vector3 pos);
	/**
		 * @brief ���f���̉�]��ݒ肷��
		 * @param qRot ��]
		*/
	void SetRotation(Quaternion qRot);
	/**
		 * @brief ���f���̊g�嗦��ݒ肷��
		 * @param scale �g�嗦
		*/
	void SetScale(Vector3 scale);
	
	/**
		 * @brief ���f���̍��W���擾
		 * @return ���W
		*/
	Vector3 GetPosition()
	{
		return m_position;
	}
	/**
		 * @brief ���f���̉�]���擾
		 * @return ��]
		*/
	Quaternion GetRotation()
	{
		return m_qRot;
	}

	/**
	 * @brief ���f���̊g�嗦���擾
	 * @return �g�嗦
	*/
	Vector3 GetScale()
	{
		return m_scale;
	}
private:
	
	Skeleton m_skeleton; //�X�P���g��
	Model m_model; //���f��
	Vector3 m_position; //���W
	Quaternion m_qRot; //��]
	Vector3 m_scale; //�g�嗦

};

