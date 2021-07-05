/*!
 *@brief	CGameObjectのマネージャ
 */
#include "stdafx.h"
#include "ExEngine.h"
#include "GameObjectManager.h"

GameObjectManager* GameObjectManager::m_instance = nullptr;

GameObjectManager::GameObjectManager()
{
	if (m_instance != nullptr) {
		//インスタンスがすでに作られている。
		std::abort();
	}
	m_instance = this;
}
GameObjectManager::~GameObjectManager()
{
	m_instance = nullptr;
}
void GameObjectManager::ExecuteUpdate()
{
	//死亡フラグがついているゲームオブジェクトを破棄する。
	for (auto& goList : m_gameObjectListArray) {
		goList.remove_if([&](IGameObject* go) {
			if (go->IsDead()) {
				delete go;
				return true;
			}
			return false;
			});
	}

	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->StartWrapper();
		}
	}


	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->UpdateWrapper();
		}
	}
}
void GameObjectManager::ExecuteRender(RenderContext& rc)
{

	//レンダラーを変更するならここを改造していくと良い。

	//TODO:暫定処理、フラグ含め別の形にしたい
	//影を先に描いてからモデルに描いた影を描き足すので先にシャドウマップをつくる。
	PostEffectManager::GetInstance()->ShadowRender(rc);

	//shadow
	if (PostEffectManager::GetInstance()->GetShadowFlag())
	{
		rc.SetStep(RenderContext::eStep_RenderShadowMap);
		//ShadowRenderでビューポートを設定しているのでここでビューポート設定しなくてOK(たぶん)
		for (auto& goList : m_gameObjectListArray) {
			for (auto& go : goList) {
				go->RenderWrapper(rc);
			}
		}
	}
	PostEffectManager::GetInstance()->EndShadowRender(rc);

	//ポストエフェクト用。Render前の処理
	PostEffectManager::GetInstance()->BeforeRender(rc);


	//1画面のスプライトのアスペクト比に合わせる。
	g_camera2D->SetWidth(g_graphicsEngine->GetFrameBufferWidth());

	rc.SetStep(RenderContext::eStep_Render);
	D3D12_VIEWPORT viewport;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = g_graphicsEngine->GetFrameBufferWidth();
	viewport.Height = g_graphicsEngine->GetFrameBufferHeight();
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	rc.SetViewport(viewport);
	//1P側の画面のカメラは1Pのカメラ(g_camera3D[0])
	LightManager::GetInstance()->UpdateEyePos();
	//g_camera3D->SetAspect(1);
	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->RenderWrapper(rc);
		}
	}

	//1画面オンリーのエフェクト更新
	EffectEngine::GetInstance()->Update(GameTime::GetInstance().GetFrameDeltaTime());
	//1画面オンリーのエフェクト描画
	EffectEngine::GetInstance()->Draw();


	//Level2D用　
	//レベル2Dは全部スプライトなのでExecuteRenderにはいらないのでは?
	//だがviewportをセットしないと画面が半分のままなのでセットはしてみる。
	{
		g_camera2D->SetWidth(g_graphicsEngine->GetFrameBufferWidth());

		rc.SetStep(RenderContext::eStep_Render);
		D3D12_VIEWPORT viewport;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = g_graphicsEngine->GetFrameBufferWidth();
		viewport.Height = g_graphicsEngine->GetFrameBufferHeight();
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		rc.SetViewport(viewport);
		for (auto& goList : m_gameObjectListArray) {
			for (auto& go : goList) {
				go->RenderWrapper(rc);
			}
		}
	}

	//ポストエフェクト用。Render後の処理
	PostEffectManager::GetInstance()->AfterRender(rc);

}

void GameObjectManager::ExecutePostRender(RenderContext& rc)
{
	if (m_rc == nullptr) {
		m_rc = &rc;
	}



	//1画面のスプライトのアスペクト比に合わせる。
	g_camera2D->SetWidth(g_graphicsEngine->GetFrameBufferWidth());

	rc.SetStep(RenderContext::eStep_Render);
	D3D12_VIEWPORT viewport;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = g_graphicsEngine->GetFrameBufferWidth();
	viewport.Height = g_graphicsEngine->GetFrameBufferHeight();
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	rc.SetViewport(viewport);
	//1P側の画面のカメラは1Pのカメラ(g_camera3D[0])
	LightManager::GetInstance()->UpdateEyePos();
	//g_camera3D->SetAspect(1);
	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->PostRenderWrapper(rc);
		}
	}


}