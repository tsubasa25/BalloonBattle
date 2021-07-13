#include "stdafx.h"
#include "Sky.h"
void Sky::Init(const wchar_t* filePath)
{
	//モデルのファイルパスの指定
	ModelInitData initData;
	initData.m_tkmFilePath = "Assets/modelData/skyCube.tkm";

	//シェーダーパスの指定
	initData.m_fxFilePath = "Assets/shader/Sky.fx";
	
	//シェーダーの頂点シェーダーのエントリー関数名の指定
	initData.m_vsEntryPointFunc = "VSMain";

	//シェーダーのピクセルシェーダーのエントリー関数名の指定
	initData.m_vsSkinEntryPointFunc = "VSSkinMain";

	initData.m_psEntryPointFunc = "PSMain_SkyCube";

	//カラーバッファのフォーマットを指定
	initData.m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;

	//モデルデータの上方向の軸を指定
	initData.m_modelUpAxis = enModelUpAxisZ;

	m_skyTexture.InitFromDDSFile(filePath);//テクスチャのファイルパス
	
	initData.m_expandShaderResoruceView[0] = &m_skyTexture;

	//initData.m_expandConstantBuffer[0] = &m_skyTexture;
	//initData.m_expandConstantBufferSize[0] = sizeof(m_skyTexture);

	//モデルの初期化
	m_model.Init(initData);
}
void Sky::Render(RenderContext& rc, Camera* camera)
{	
	if (rc.GetRenderStep() == RenderContext::eStep_Render) {
		m_model.Draw(rc, camera);
	}
}
void Sky::Update()
{	
	m_model.UpdateWorldMatrix(m_position, m_qRot, m_scale);
}