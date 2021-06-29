#include "stdafx.h" 
#include "system/system.h"
#include "Player.h"
#include "GameScene.h"
#include "BackGround.h"
#include "TitleScene.h"
///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐�
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    // �Q�[���̏�����
    InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

    //////////////////////////////////////
    // �������珉�������s���R�[�h���L�q����
    //////////////////////////////////////

    //�Q�[���I�u�W�F�N�g�}�l�[�W���[�̃C���X�^���X���쐬����B
    GameObjectManager::CreateInstance();
    PhysicsWorld::CreateInstance();
    //���C�g�}�l�[�W���[�̃C���X�^���X���쐬   
    LightManager::CreateInstance();

    EffectEngine::CreateInstance();

    TitleScene* titleScene = NewGO<TitleScene>(0, "titleScene");
   /* GameScene*gameScene=NewGO<GameScene>(0,"gameScene");*/   
   /* NewGO<BackGround>(0);*/

    g_camera3D->SetPosition({ 0.0f, 1600.0f, -1000.0f });
    g_camera3D->SetTarget({ 0,100,-300 });    
    
    //////////////////////////////////////
    // ���������s���R�[�h�������̂͂����܂ŁI�I�I
    //////////////////////////////////////
    auto& renderContext = g_graphicsEngine->GetRenderContext();

    // ��������Q�[�����[�v
    while (DispatchWindowMessage())
    {
        // �����_�����O�J�n
        g_engine->BeginFrame();
        GameObjectManager::GetInstance()->ExecuteUpdate();
        GameObjectManager::GetInstance()->ExecuteRender(renderContext);
       
        //////////////////////////////////////
        // ��������G��`���R�[�h���L�q����
        //////////////////////////////////////
       
        
        LightManager::GetInstance()->UpdateEyePos();
       
        EffectEngine::GetInstance()->Update(g_gameTime->GetFrameDeltaTime());
        EffectEngine::GetInstance()->Draw();
        //////////////////////////////////////
        // �G��`���R�[�h�������̂͂����܂ŁI�I�I
        //////////////////////////////////////
        // �����_�����O�I��
        g_engine->EndFrame();
    }
    return 0;
}
