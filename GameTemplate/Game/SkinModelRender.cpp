#include "stdafx.h"
#include "SkinModelRender.h"
#include "DirectionLight.h"
#include "SpotLight.h"
#include "PointLight.h"

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
	//���f���̃t�@�C���p�X�̎w��
	initData.m_tkmFilePath = modelPath;
	//�V�F�[�_�[�p�X�̎w��
	initData.m_fxFilePath = "Assets/shader/model.fx";
	//�J���[�o�b�t�@�̃t�H�[�}�b�g���w��
	initData.m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;
	
	//���f���f�[�^�̏�����̎����w��
	initData.m_modelUpAxis = enModelUpAxisZ;
	
	//�萔�o�b�t�@�����f���ɕR�t����
	initData.m_expandConstantBuffer = LightManager::GetInstance()->GetLigDatas();
	initData.m_expandConstantBufferSize = LightManager::GetInstance()->GetLigDataSize();
	//////////////////////////////////////////////
	//���f���̏�����
	m_model.Init(initData);
	
}
void SkinModelRender::Init(const char* modelPath, const char* skeletonPath)
{
	Init(modelPath, skeletonPath, nullptr, 0);
}

void SkinModelRender::Init(const char* modelPath)
{
	Init(modelPath, nullptr, nullptr, 0);
}
void SkinModelRender::Render(RenderContext& rc)
{
	//�����_�[�R���e�L�X�g�̕`���ŕ���
	m_model.Draw(rc);
}
void SkinModelRender::UpdateModel()
{
	//���f�����A�b�v�f�[�g
	//for (auto& model : m_model) {
		m_model.UpdateWorldMatrix(m_position, m_qRot, m_scale);
		m_skeleton.Update(m_model.GetWorldMatrix());
	
}

void SkinModelRender::SetPosition(Vector3 pos)
{
	m_position = pos;

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
