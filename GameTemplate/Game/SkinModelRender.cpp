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
	//モデルの初期化データ
	ModelInitData initData;

	//影の初期化データ
	ModelInitData shadowModelInitData;

	//モデルのファイルパスの指定
	initData.m_tkmFilePath = modelPath;
	shadowModelInitData.m_tkmFilePath = modelPath;
	
	//シェーダーパスの指定
	initData.m_fxFilePath = "Assets/shader/shadowReceiver.fx";
	shadowModelInitData.m_fxFilePath = "Assets/shader/shadow.fx";
	
	//シェーダーの頂点シェーダーのエントリー関数名の指定
	initData.m_vsEntryPointFunc = "VSMain";
	shadowModelInitData.m_vsEntryPointFunc = "VSMain";
	
	//シェーダーのピクセルシェーダーのエントリー関数名の指定
	initData.m_vsSkinEntryPointFunc = "VSSkinMain";
	shadowModelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
	
	//スケルトンが存在している時はスケルトンを初期化
	if (skeletonPath != nullptr)
	{
		m_skeleton.Init(skeletonPath);
		initData.m_skeleton = &m_skeleton;
		shadowModelInitData.m_skeleton = &m_skeleton;
	}
	//カラーバッファのフォーマットを指定
	initData.m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;
	shadowModelInitData.m_colorBufferFormat = DXGI_FORMAT_R32_FLOAT;
	
	//モデルデータの上方向の軸を指定
	initData.m_modelUpAxis = enModelUpAxisZ;
	shadowModelInitData.m_modelUpAxis = enModelUpAxisZ;


	//モデルに影を落とすために影のテクスチャを紐付ける
	initData.m_expandShaderResoruceView[0] = &PostEffectManager::GetInstance()->GetShadowMap();
	
	//定数バッファをモデルに紐付ける
	initData.m_expandConstantBufferSize[0] = LightManager::GetInstance()->GetLigDataSize();
	shadowModelInitData.m_expandConstantBufferSize[0] = LightManager::GetInstance()->GetLigCameraDataSize();
	initData.m_expandConstantBuffer[0] = LightManager::GetInstance()->GetLigDatas();
	shadowModelInitData.m_expandConstantBuffer[0] = LightManager::GetInstance()->GetLigCameraDatas();

	initData.m_expandConstantBufferSize[1] = LightManager::GetInstance()->GetLigCameraDataSize();
	initData.m_expandConstantBuffer[1] = LightManager::GetInstance()->GetLigCameraDatas();
	
	//モデルの初期化
	m_model[eModel].Init(initData);

	//影描画モデルの初期化
	m_model[eModel_Shadow].Init(shadowModelInitData);

	//アニメーション関連の初期化
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
	//レンダーコンテキストの描画先で分岐
	switch (rc.GetRenderStep()) {
	case RenderContext::eStep_Render:
		//画面1に描画
		m_model[eModel].Draw(rc, camera);
		break;
	
	case RenderContext::eStep_RenderShadowMap:
		//影を作るモデルの時だけ影を描画
		if (m_isShadowCaster)
		{
			m_model[eModel_Shadow].Draw(rc, camera);
		}
		break;
	}
	
}
void SkinModelRender::UpdateModel()
{
	//モデルをアップデート
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
		//未登録
		tkmFile = new TkmFile;
		tkmFile->Load(tkmFilePath);
		ResourceBankManager::GetInstance()->RegistTkmFileToBank(tkmFilePath, tkmFile);
	}
}