#include "stdafx.h"
#include "Model.h"
#include "Material.h"

void Model::Init(const ModelInitData& m_initData)
{
	MY_ASSERT(
		m_initData.m_fxFilePath, 
		"error : initData.m_fxFilePath���w�肳��Ă��܂���B"
	);
	MY_ASSERT(
		m_initData.m_tkmFilePath,
		"error : initData.m_tkmFilePath���w�肳��Ă��܂���B"
	);
	//�����̃V�F�[�_�[�����[�h���鏈�������߂Ă���̂�
	//wchar_t�^�̕�����Ȃ̂ŁA�����ŕϊ����Ă����B
	wchar_t wfxFilePath[256] = {L""};
	if (m_initData.m_fxFilePath != nullptr) {
		//MessageBoxA(nullptr, "fx�t�@�C���p�X���w�肳��Ă��܂���B", "�G���[", MB_OK);
		//std::abort();
		mbstowcs(wfxFilePath, m_initData.m_fxFilePath, 256);
	}
	
	if (m_initData.m_skeleton != nullptr) {
		//�X�P���g�����w�肳��Ă���B
		m_meshParts.BindSkeleton(*m_initData.m_skeleton);
	}
	
	m_modelUpAxis = m_initData.m_modelUpAxis;
	m_tkmFile = ResourceBankManager::GetInstance()->GetTkmFileFromBank(m_initData.m_tkmFilePath);

	if (m_tkmFile == nullptr)
	{
		//���o�^
		m_tkmFile = new TkmFile;
		m_tkmFile->Load(m_initData.m_tkmFilePath);
		ResourceBankManager::GetInstance()->RegistTkmFileToBank(m_initData.m_tkmFilePath, m_tkmFile);
	}
	m_meshParts.InitFromTkmFile(
		*m_tkmFile,
		wfxFilePath,
		m_initData.m_vsEntryPointFunc,
		m_initData.m_vsSkinEntryPointFunc,
		m_initData.m_psEntryPointFunc,
		m_initData.m_expandConstantBuffer,
		m_initData.m_expandConstantBufferSize,
		m_initData.m_expandShaderResoruceView[0],
		m_initData.m_colorBufferFormat
	);

	UpdateWorldMatrix(g_vec3Zero, g_quatIdentity, g_vec3One);

}

void Model::UpdateWorldMatrix(Vector3 pos, Quaternion rot, Vector3 scale)
{
	Matrix mBias;
	if (m_modelUpAxis == enModelUpAxisZ) {
		//Z-up
		mBias.MakeRotationX(Math::PI * -0.5f);
	}
	Matrix mTrans, mRot, mScale;
	mTrans.MakeTranslation(pos);
	mRot.MakeRotationFromQuaternion(rot);
	mScale.MakeScaling(scale);
	m_world = mBias * mScale * mRot * mTrans;
}
void Model::UpdateWorldMatrix(Matrix world)
{
	m_world = world;
}
void Model::ChangeAlbedoMap(const char* materialName, Texture& albedoMap)
{
	m_meshParts.QueryMeshs([&](const SMesh& mesh) {
		//todo �}�e���A������tkm�t�@�C���ɏo�͂����Ȃ������E�E�E�B
		//todo ���͑S�}�e���A�������ւ��܂�
		for (Material* material : mesh.m_materials) {
			material->GetAlbedoMap().InitFromD3DResource(albedoMap.Get());
		}
	});
	//�f�B�X�N���v�^�q�[�v�̍č쐬�B
	m_meshParts.CreateDescriptorHeaps();
	
}
void Model::Draw(RenderContext& rc,Camera*camera)
{
	m_meshParts.Draw(
		rc, 
		m_world, 
		camera->GetViewMatrix(), 
		camera->GetProjectionMatrix()
	);
}
