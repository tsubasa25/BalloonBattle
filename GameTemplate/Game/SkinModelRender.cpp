#include "stdafx.h"
#include "SkinModelRender.h"
//#include "DirectionLight.h"
//#include "SpotLight.h"
//#include "PointLight.h"

SkinModelRender::~SkinModelRender()
{

}
void SkinModelRender::Update()
{

}
void SkinModelRender::Init(const char* modelPath, const char* skeletonPath, AnimationClip* animClips, int animClipNum)
{
	//���f���̏������f�[�^
	ModelInitData initData;

	//�e�̏������f�[�^
	ModelInitData shadowModelInitData;

	//���f���̃t�@�C���p�X�̎w��
	initData.m_tkmFilePath = modelPath;
	shadowModelInitData.m_tkmFilePath = modelPath;
	
	//�V�F�[�_�[�p�X�̎w��
	initData.m_fxFilePath = "Assets/shader/shadowReceiver.fx";
	shadowModelInitData.m_fxFilePath = "Assets/shader/shadow.fx";
	
	//�V�F�[�_�[�̒��_�V�F�[�_�[�̃G���g���[�֐����̎w��
	initData.m_vsEntryPointFunc = "VSMain";
	shadowModelInitData.m_vsEntryPointFunc = "VSMain";
	
	//�V�F�[�_�[�̃s�N�Z���V�F�[�_�[�̃G���g���[�֐����̎w��
	initData.m_vsSkinEntryPointFunc = "VSSkinMain";
	shadowModelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
	
	//�X�P���g�������݂��Ă��鎞�̓X�P���g����������
	if (skeletonPath != nullptr)
	{
		m_skeleton.Init(skeletonPath);
		initData.m_skeleton = &m_skeleton;
		shadowModelInitData.m_skeleton = &m_skeleton;
	}
	//�J���[�o�b�t�@�̃t�H�[�}�b�g���w��
	initData.m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;
	shadowModelInitData.m_colorBufferFormat = DXGI_FORMAT_R32_FLOAT;
	
	//���f���f�[�^�̏�����̎����w��
	initData.m_modelUpAxis = enModelUpAxisZ;
	shadowModelInitData.m_modelUpAxis = enModelUpAxisZ;


	//���f���ɉe�𗎂Ƃ����߂ɉe�̃e�N�X�`����R�t����
	initData.m_expandShaderResoruceView[0] = &PostEffectManager::GetInstance()->GetShadowMap();
	
	//�萔�o�b�t�@�����f���ɕR�t����
	initData.m_expandConstantBufferSize[0] = LightManager::GetInstance()->GetLigDataSize();
	shadowModelInitData.m_expandConstantBufferSize[0] = LightManager::GetInstance()->GetLigCameraDataSize();
	initData.m_expandConstantBuffer[0] = LightManager::GetInstance()->GetLigDatas();
	shadowModelInitData.m_expandConstantBuffer[0] = LightManager::GetInstance()->GetLigCameraDatas();

	initData.m_expandConstantBufferSize[1] = LightManager::GetInstance()->GetLigCameraDataSize();
	initData.m_expandConstantBuffer[1] = LightManager::GetInstance()->GetLigCameraDatas();
	
	//���f���̏�����
	m_model[eModel].Init(initData);

	//�e�`�惂�f���̏�����
	m_model[eModel_Shadow].Init(shadowModelInitData);

	//�A�j���[�V�����֘A�̏�����
	m_animationClips = animClips;
	m_animationClipNum = animClipNum;

	if (m_animationClips != nullptr)
	{
		m_animation.Init(m_skeleton, m_animationClips, m_animationClipNum);
	}
}
void SkinModelRender::Init(const char* modelPath, const char* skeletonPath)
{
	Init(modelPath, skeletonPath, nullptr, 0);
}

void SkinModelRender::Init(const char* modelPath)
{
	Init(modelPath, nullptr, nullptr, 0);
}
void SkinModelRender::Render(RenderContext& rc, Camera* camera)
{
	//�����_�[�R���e�L�X�g�̕`���ŕ���
	switch (rc.GetRenderStep()) {
	case RenderContext::eStep_Render:
		//���1�ɕ`��
		m_model[eModel].Draw(rc, camera);
		break;
	
	case RenderContext::eStep_RenderShadowMap:
		//�e����郂�f���̎������e��`��
		if (m_isShadowCaster)
		{
			m_model[eModel_Shadow].Draw(rc, camera);
		}
		break;
	}
	
}
void SkinModelRender::UpdateModel()
{
	//���f�����A�b�v�f�[�g
	for (auto& model : m_model) {
		model.UpdateWorldMatrix(m_position, m_qRot, m_scale);
		m_skeleton.Update(model.GetWorldMatrix());
	}	
}

void SkinModelRender::SetPosition(Vector3 pos)
{
	m_position = pos;
	UpdateModel();
}
void SkinModelRender::SetPositionX(float posX)
{
	m_position.x = posX;
	UpdateModel();
}
void SkinModelRender::SetPositionZ(float posZ)
{
	m_position.z = posZ;
	UpdateModel();
}

void SkinModelRender::SetRotation(Quaternion qRot)
{
	m_qRot = qRot;
	UpdateModel();
}

void SkinModelRender::SetScale(Vector3 scale)
{
	m_scale = scale;
	UpdateModel();
}
void SkinModelRender::PreLoadModel(const char* tkmFilePath)
{
	TkmFile* tkmFile = ResourceBankManager::GetInstance()->GetTkmFileFromBank(tkmFilePath);

	if (tkmFile == nullptr)
	{
		//���o�^
		tkmFile = new TkmFile;
		tkmFile->Load(tkmFilePath);
		ResourceBankManager::GetInstance()->RegistTkmFileToBank(tkmFilePath, tkmFile);
	}
}