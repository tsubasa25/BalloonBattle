#include "stdafx.h"
#include "Model.h"
#include "Material.h"
#include "../GameTemplate/Game/ResourceBankManager.h"
void Model::Init(const ModelInitData& m_initData)
{
	MY_ASSERT(
		m_initData.m_fxFilePath, 
		"error : initData.m_fxFilePathが指定されていません。"
	);
	MY_ASSERT(
		m_initData.m_tkmFilePath,
		"error : initData.m_tkmFilePathが指定されていません。"
	);
	//内部のシェーダーをロードする処理が求めているのが
	//wchar_t型の文字列なので、ここで変換しておく。
	wchar_t wfxFilePath[256] = {L""};
	if (m_initData.m_fxFilePath != nullptr) {
		//MessageBoxA(nullptr, "fxファイルパスが指定されていません。", "エラー", MB_OK);
		//std::abort();
		mbstowcs(wfxFilePath, m_initData.m_fxFilePath, 256);
	}
	
	if (m_initData.m_skeleton != nullptr) {
		//スケルトンが指定されている。
		m_meshParts.BindSkeleton(*m_initData.m_skeleton);
	}
	
	m_modelUpAxis = m_initData.m_modelUpAxis;
	m_tkmFile = nsBalloon::ResourceBankManager::GetInstance()->GetTkmFileFromBank(m_initData.m_tkmFilePath);

	if (m_tkmFile == nullptr)
	{
		//未登録
		m_tkmFile = new TkmFile;
		m_tkmFile->Load(m_initData.m_tkmFilePath);
		nsBalloon::ResourceBankManager::GetInstance()->RegistTkmFileToBank(m_initData.m_tkmFilePath, m_tkmFile);
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
		//todo マテリアル名をtkmファイルに出力したなかった・・・。
		//todo 今は全マテリアル差し替えます
		for (Material* material : mesh.m_materials) {
			material->GetAlbedoMap().InitFromD3DResource(albedoMap.Get());
		}
	});
	//ディスクリプタヒープの再作成。
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