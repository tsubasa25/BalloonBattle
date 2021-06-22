#pragma once

#include <map>
#include <string>
/// <summary>
/// �G�t�F�N�g�G���W���N���X�B
/// </summary>
class EffectEngine {
	static EffectEngine* m_instance;	//�B��̃C���X�^���X�B
	//3D�p
	EffekseerRenderer::RendererRef m_renderer[2];	//�����_���[�B
	Effekseer::RefPtr<EffekseerRenderer::SingleFrameMemoryPool> m_memoryPool[2];	//�������v�[���B
	Effekseer::RefPtr<EffekseerRenderer::CommandList> m_commandList[2];			//�R�}���h���X�g�B
	Effekseer::ManagerRef m_manager[2];

	//2D�p
	EffekseerRenderer::RendererRef m_2Drenderer;//2D�p�����_���[�B
	Effekseer::RefPtr<EffekseerRenderer::SingleFrameMemoryPool> m_2DmemoryPool;	//2D�p�������v�[���B
	Effekseer::RefPtr<EffekseerRenderer::CommandList> m_2DcommandList;			//�R�}���h���X�g�B
	Effekseer::ManagerRef m_2Dmanager;

	//FlyWeight�p
	std::map< std::u16string, Effekseer::EffectRef > m_effectMap;
public:
	/// <summary>
	/// �C���X�^���X�̍쐬�B
	/// </summary>
	static void CreateInstance()
	{
		if (m_instance == nullptr) {
			m_instance = new EffectEngine;
		}
	}

	/// <summary>
	/// �C���X�^���X�̎擾�B
	/// </summary>
	/// <returns></returns>
	static EffectEngine* GetInstance()
	{
		return m_instance;
	}

	/// <summary>
	/// �C���X�^���X�̍폜�B
	/// </summary>
	static void DeleteInstance()
	{
		delete m_instance;
		m_instance = nullptr;

	}

	/// <summary>
	/// �G�t�F�N�g���Đ���������B
	/// </summary>
	/// <param name="handle"></param>
	/// <returns></returns>
	bool IsPlay(int handle) const
	{
		//NOTE:2�̃G�t�F�N�g���ʁX�ɍĐ�����邱�Ƃ͂Ȃ��̂�m_manager[0]�̌��ʂ�Ԃ��Α��v?
		return m_manager[0]->GetShown(handle);
	}

	/// <summary>
	/// �G�t�F�N�g�̃��[���h�s����X�V�B
	/// </summary>
	/// <param name="handle"></param>
	/// <param name="pos"></param>
	/// <param name="rot"></param>
	/// <param name="scale"></param>
	void UpdateEffectWorldMatrix(int handle, Vector3 pos, Quaternion rot, Vector3 scale)
	{
		Matrix mTrans, mRot, mScale, mBase;
		mTrans.MakeTranslation(pos);
		mRot.MakeRotationFromQuaternion(rot);
		mScale.MakeScaling(scale);
		mBase = mScale * mRot;
		mBase = mBase * mTrans;

		Effekseer::Matrix43 baseMat;
		baseMat.Value[0][0] = mBase.m[0][0];
		baseMat.Value[0][1] = mBase.m[0][1];
		baseMat.Value[0][2] = mBase.m[0][2];

		baseMat.Value[1][0] = mBase.m[1][0];
		baseMat.Value[1][1] = mBase.m[1][1];
		baseMat.Value[1][2] = mBase.m[1][2];

		baseMat.Value[2][0] = mBase.m[2][0];
		baseMat.Value[2][1] = mBase.m[2][1];
		baseMat.Value[2][2] = mBase.m[2][2];

		baseMat.Value[3][0] = mBase.m[3][0];
		baseMat.Value[3][1] = mBase.m[3][1];
		baseMat.Value[3][2] = mBase.m[3][2];

		m_manager[0]->SetBaseMatrix(handle, baseMat);
		
	}

	/// <summary>
	/// �G�t�F�N�g���Đ��B
	/// </summary>
	/// <param name="filePath">�Đ��������G�t�F�N�g</param>
	/// <returns>�Đ������G�t�F�N�g�̃n���h���B</returns>
	int Play(Effekseer::EffectRef effect);

	/// <summary>
	/// �G�t�F�N�g���~�B
	/// </summary>
	/// <param name="effectHandle"></param>
	void Stop(int effectHandle);

	/// <summary>
	/// �G�t�F�N�g�����[�h�B
	/// </summary>
	Effekseer::EffectRef LoadEffect(const char16_t* filePath);

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="deltaTime">1�t���[���̌o�ߎ��ԁB</param>
	void Update(float deltaTime);

	/// <summary>
	/// �`��B
	/// </summary>
	void Draw(int cameraNum);

	/// <summary>
	/// 2D�G�t�F�N�g���Đ���������B
	/// </summary>
	/// <param name="handle"></param>
	/// <returns></returns>
	bool IsPlay2D(int handle) const
	{
		return m_2Dmanager->GetShown(handle);
	}

	/// <summary>
	/// 2D�G�t�F�N�g�̃��[���h�s����X�V�B
	/// </summary>
	/// <param name="handle"></param>
	/// <param name="pos"></param>
	/// <param name="rot"></param>
	/// <param name="scale"></param>
	void UpdateEffectWorldMatrix2D(int handle, Vector3 pos, Quaternion rot, Vector3 scale)
	{
		Matrix mTrans, mRot, mScale, mBase;
		mTrans.MakeTranslation(pos);
		mRot.MakeRotationFromQuaternion(rot);
		mScale.MakeScaling(scale);
		mBase = mScale * mRot;
		mBase = mBase * mTrans;

		Effekseer::Matrix43 baseMat;
		baseMat.Value[0][0] = mBase.m[0][0];
		baseMat.Value[0][1] = mBase.m[0][1];
		baseMat.Value[0][2] = mBase.m[0][2];

		baseMat.Value[1][0] = mBase.m[1][0];
		baseMat.Value[1][1] = mBase.m[1][1];
		baseMat.Value[1][2] = mBase.m[1][2];

		baseMat.Value[2][0] = mBase.m[2][0];
		baseMat.Value[2][1] = mBase.m[2][1];
		baseMat.Value[2][2] = mBase.m[2][2];

		baseMat.Value[3][0] = mBase.m[3][0];
		baseMat.Value[3][1] = mBase.m[3][1];
		baseMat.Value[3][2] = mBase.m[3][2];

		m_2Dmanager->SetBaseMatrix(handle, baseMat);
	}

	/// <summary>
	/// 2D�G�t�F�N�g���Đ��B
	/// </summary>
	/// <param name="filePath">�Đ��������G�t�F�N�g</param>
	/// <returns>�Đ������G�t�F�N�g�̃n���h���B</returns>
	int Play2D(Effekseer::EffectRef effect);

	/// <summary>
	/// 2D�G�t�F�N�g���~�B
	/// </summary>
	/// <param name="effectHandle"></param>
	void Stop2D(int effectHandle);

	/// <summary>
	/// 2D�G�t�F�N�g�����[�h�B
	/// </summary>
	Effekseer::EffectRef LoadEffect2D(const char16_t* filePath);

	/// <summary>
	/// 2D�G�t�F�N�g���X�V
	/// </summary>
	/// <param name="deltaTime">1�t���[���̌o�ߎ��ԁB</param>
	void Update2D(float deltaTime);

	/// <summary>
	/// 2D�G�t�F�N�g��`��B
	/// </summary>
	void Draw2D();
private:
	EffectEngine();
	~EffectEngine();
};
