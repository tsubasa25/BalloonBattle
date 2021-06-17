#include "stdafx.h" 
#include "system/system.h"
#include "Player.h"
#include "GameScene.h"
#include "BackGround.h"
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

    NewGO<GameScene>(0);
    NewGO<BackGround>(0);
   
    PointLight* pointLight = nullptr;
    pointLight = NewGO<PointLight>(0);   
    pointLight->SetColor({ 10,0,10 });
    pointLight->SetRange(200);
    pointLight->SetPosition({ Vector3::Zero });
    SpotLight* spotLight = nullptr;
    spotLight = NewGO<SpotLight>(0);
    spotLight->SetColor({ 10,0,0 });
    spotLight->SetDirection({ 1,0,0 });
    spotLight->SetPosition({ 0,50,50 });
    spotLight->SetRange(1000);
    spotLight->SetAngleDeg(30);
   
    g_camera3D->SetPosition({ 0.0f, 1000.0f, 1500.0f });
    g_camera3D->SetTarget({ 0,50,0 });
    
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
        //////////////////////////////////////
        // �G��`���R�[�h�������̂͂����܂ŁI�I�I
        //////////////////////////////////////
        // �����_�����O�I��
        g_engine->EndFrame();
    }
    return 0;
}
