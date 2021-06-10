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
	//モデルの初期化データ
	ModelInitData initData;
	//モデルのファイルパスの指定
	initData.m_tkmFilePath = modelPath;
	//シェーダーパスの指定
	initData.m_fxFilePath = "Assets/shader/model.fx";
	//カラーバッファのフォーマットを指定
	initData.m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;
	
	//モデルデータの上方向の軸を指定
	initData.m_modelUpAxis = enModelUpAxisZ;
	
	//定数バッファをモデルに紐付ける
	initData.m_expandConstantBuffer = LightManager::GetInstance()->GetLigDatas();
	initData.m_expandConstantBufferSize = LightManager::GetInstance()->GetLigDataSize();
	//////////////////////////////////////////////
	//モデルの初期化
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
	//レンダーコンテキストの描画先で分岐
	m_model.Draw(rc);
}
void SkinModelRender::UpdateModel()
{
	//モデルをアップデート
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
