#pragma once
class Effect :public IGameObject
{
public:
	Effect();
	~Effect();

	/**
	 * @brief �G�t�F�N�g�̏�����
	 * @param filePath �G�t�F�N�g�̃t�@�C���p�X
	*/
	void Init(const char16_t* filePath);

	/**
	 * @brief �G�t�F�N�g�̍Đ�
	*/
	void Play();

	/**
	 * @brief �G�t�F�N�g�̍Đ����I��
	*/
	void Stop();

	/**
	 * @brief �G�t�F�N�g�̍��W��ݒ�
	 * @param pos ���W
	*/
	void SetPosition(const Vector3& pos)
	{
		m_position = pos;
	}

	/**
	 * @brief �G�t�F�N�g�̍��W���擾
	 * @return ���W
	*/
	const Vector3& GetPosition() const
	{
		return m_position;
	}

	/**
	 * @brief �G�t�F�N�g�̉�]��ݒ�
	 * @param rot ��]
	*/
	void SetRotation(const Quaternion& rot)
	{
		m_rotation = rot;
	}

	/**
	 * @brief �G�t�F�N�g�̉�]���擾
	 * @return ��]
	*/
	const Quaternion& GetRotation() const
	{
		return m_rotation;
	}

	/**
	 * @brief �G�t�F�N�g�̊g�嗦��ݒ�
	 * @param scale �g�嗦
	*/
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}

	/**
	 * @brief �G�t�F�N�g�̊g�嗦���擾
	 * @return �g�嗦
	*/
	const Vector3& GetScale() const
	{
		return m_scale;
	}

	/**
	 * @brief �G�t�F�N�g���Đ�����
	 * @return �Đ���:true �Đ����Ă��Ȃ�:false
	*/
	bool IsPlay() const
	{
		return EffectEngine::GetInstance()->IsPlay(m_handle);
	}

	/**
	 * @brief �G�t�F�N�g�̍X�V
	*/
	void Update();

	/**
	 * @brief ���O�ɃG�t�F�N�g�����[�h���Ă���
	 * @param filePath ���[�h�������G�t�F�N�g�̃t�@�C���p�X
	*/
	static void PreLoadEffect(const char16_t* filePath)
	{
		EffectEngine::GetInstance()->LoadEffect(filePath);
	}
private:
	Effekseer::EffectRef m_effect;	//�G�t�F�N�g
	int	m_handle = -1;				//�Đ����̃G�t�F�N�g�̃n���h���B
	Vector3 m_position;				//���W�B
	Quaternion m_rotation;;			//��]�B
	Vector3 m_scale = g_vec3One;	//�g�嗦�B
};
