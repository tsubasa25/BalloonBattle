/*!
 *@brief	CGameObject�̃}�l�[�W��
 */
#include "stdafx.h"
#include "ExEngine.h"
#include "GameObjectManager.h"

GameObjectManager* GameObjectManager::m_instance = nullptr;

GameObjectManager::GameObjectManager()
{
	if (m_instance != nullptr) {
		//�C���X�^���X�����łɍ���Ă���B
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
	//���S�t���O�����Ă���Q�[���I�u�W�F�N�g��j������B
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

	//�����_���[��ύX����Ȃ炱�����������Ă����Ɨǂ��B

	//TODO:�b�菈���A�t���O�܂ߕʂ̌`�ɂ�����
	//�e���ɕ`���Ă��烂�f���ɕ`�����e��`�������̂Ő�ɃV���h�E�}�b�v������B
	PostEffectManager::GetInstance()->ShadowRender(rc);

	//shadow
	if (PostEffectManager::GetInstance()->GetShadowFlag())
	{
		rc.SetStep(RenderContext::eStep_RenderShadowMap);
		//ShadowRender�Ńr���[�|�[�g��ݒ肵�Ă���̂ł����Ńr���[�|�[�g�ݒ肵�Ȃ���OK(���Ԃ�)
		for (auto& goList : m_gameObjectListArray) {
			for (auto& go : goList) {
				go->RenderWrapper(rc, LightManager::GetInstance()->GetLightCamera());
			}
		}
	}
	PostEffectManager::GetInstance()->EndShadowRender(rc);

	//�|�X�g�G�t�F�N�g�p�BRender�O�̏���
	PostEffectManager::GetInstance()->BeforeRender(rc);


	//1��ʂ̃X�v���C�g�̃A�X�y�N�g��ɍ��킹��B
	//g_camera2D->SetWidth(g_graphicsEngine->GetFrameBufferWidth());

	rc.SetStep(RenderContext::eStep_Render);
	D3D12_VIEWPORT viewport;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = g_graphicsEngine->GetFrameBufferWidth();
	viewport.Height = g_graphicsEngine->GetFrameBufferHeight();
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	rc.SetViewport(viewport);
	//1P���̉�ʂ̃J������1P�̃J����(g_camera3D[0])
	LightManager::GetInstance()->UpdateEyePos();
	//g_camera3D->SetAspect(1);
	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->RenderWrapper(rc, g_camera3D);
		}
	}                                           

	//1��ʃI�����[�̃G�t�F�N�g�X�V
	EffectEngine::GetInstance()->Update(GameTime::GetInstance().GetFrameDeltaTime());
	//1��ʃI�����[�̃G�t�F�N�g�`��
	EffectEngine::GetInstance()->Draw();


	//Level2D�p�@
	//���x��2D�͑S���X�v���C�g�Ȃ̂�ExecuteRender�ɂ͂���Ȃ��̂ł�?
	//����viewport���Z�b�g���Ȃ��Ɖ�ʂ������̂܂܂Ȃ̂ŃZ�b�g�͂��Ă݂�B
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
				go->RenderWrapper(rc, g_camera3D);
			}
		}
	}

	//�|�X�g�G�t�F�N�g�p�BRender��̏���
	PostEffectManager::GetInstance()->AfterRender(rc);

}

void GameObjectManager::ExecutePostRender(RenderContext& rc)
{
	if (m_rc == nullptr) {
		m_rc = &rc;
	}



	////1��ʂ̃X�v���C�g�̃A�X�y�N�g��ɍ��킹��B
	//g_camera2D->SetWidth(g_graphicsEngine->GetFrameBufferWidth());

	rc.SetStep(RenderContext::eStep_Render);
	/*D3D12_VIEWPORT viewport;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;                                   
	viewport.Width = g_graphicsEngine->GetFrameBufferWidth();
	viewport.Height = g_graphicsEngine->GetFrameBufferHeight();
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;*/
	//rc.SetViewport(viewport);
	//1P���̉�ʂ̃J������1P�̃J����(g_camera3D[0])
	//LightManager::GetInstance()->UpdateEyePos();
	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->PostRenderWrapper(rc);
		}
	}
	//Level2D�p�@
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
				go->PostRenderWrapper(rc);
			}
		}

		////2D�G�t�F�N�g�X�V
		//EffectEngine::GetInstance()->Update2D(GameTime::GetInstance().GetFrameDeltaTime());
		////2D�G�t�F�N�g�`��
		//EffectEngine::GetInstance()->Draw2D();
	}
}