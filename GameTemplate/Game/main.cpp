#include "stdafx.h" 
#include "system/system.h"
#include "Player.h"
#include "GameScene.h"
#include "BackGround.h"
#include "TitleBack.h"
#include "TitleScene.h"
namespace
{
    const Vector3 LIGHTCAMERA_POSITION = { 0.0f, 2000.0f,0.0f };
    const Vector3 LIGHTCAMERA_TARGET = { 0,0,0 };
    const Vector3 LIGHTCAMERA_UP = { 1.0f,0.0f,0.0f };
    const float LIGHTCAMERA_WIDTH = 2000.0f;
    const float LIGHTCAMERA_HEIGHT = 2000.0f;
}
void PreLoad();

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
    LightManager::GetInstance()->SetLightCameraPosition(LIGHTCAMERA_POSITION);
    LightManager::GetInstance()->SetLightCameraTarget(LIGHTCAMERA_TARGET);
    LightManager::GetInstance()->SetLightCameraUp(LIGHTCAMERA_UP);
    LightManager::GetInstance()->SetLightCameraUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Perspective); //enUpdateProjMatrixFunc_Ortho
   /* LightManager::GetInstance()->SetLightCameraWidth(LIGHTCAMERA_WIDTH);
    LightManager::GetInstance()->SetLightCameraHeight(LIGHTCAMERA_HEIGHT);*/

    //���\�[�X�}�l�[�W���̃C���X�^���X���쐬
    ResourceBankManager::CreateInstance();

    // �T�E���h�G���W���̃C���X�^���X���쐬����B
    SoundEngine::CreateInstance();
    SoundEngine::GetInstance()->Init();

    EffectEngine::CreateInstance();

    PostEffectManager::CreateInstance();
    //�u���[���t���O�A�V���h�E�t���O�̏���
    PostEffectManager::GetInstance()->Init(true, true);
    //////////////////////////////////////////////////

    //FPS�Œ�p�X�g�b�v�E�H�b�`
    Stopwatch stopwatch;

    PreLoad();
    TitleScene* titleScene = NewGO<TitleScene>(0, "titleScene");
    TitleBack* titleBack = NewGO<TitleBack>(0, "titleBack");
   /* GameScene*gameScene=NewGO<GameScene>(0,"gameScene");*/   
   /* NewGO<BackGround>(0);*/

    //g_camera3D->SetPosition({ 0.0f, 1200.0f, -1800.0f });
    //g_camera3D->SetTarget({ 0,0,-300 });
    g_camera3D->SetFar(100000.0f);
    //////////////////////////////////////
    // ���������s���R�[�h�������̂͂����܂ŁI�I�I
    //////////////////////////////////////
    auto& renderContext = g_graphicsEngine->GetRenderContext();

    // ��������Q�[�����[�v
    while (DispatchWindowMessage())
    {
        //FPS�v���p�X�g�b�v�E�H�b�`�̌v���J�n
        stopwatch.Start();

        // �����_�����O�J�n
        g_engine->BeginFrame();
      
        
        GameObjectManager::GetInstance()->ExecuteUpdate();
        GameObjectManager::GetInstance()->ExecuteRender(renderContext);
        //PostRender�̓X�v���C�g�A�t�H���g���A�G�t�F�N�g���󂯂Ȃ����̂�`�悷��
        GameObjectManager::GetInstance()->ExecutePostRender(renderContext);
        
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

void PreLoad()
{
    SkinModelRender::PreLoadModel("Assets/modelData/Balloon0.tkm");
    SkinModelRender::PreLoadModel("Assets/modelData/Balloon1.tkm");
    SkinModelRender::PreLoadModel("Assets/modelData/Balloon2.tkm");
    SkinModelRender::PreLoadModel("Assets/modelData/Balloon3.tkm");
    SkinModelRender::PreLoadModel("Assets/modelData/Balloon4.tkm");
    SkinModelRender::PreLoadModel("Assets/modelData/Balloon5.tkm"); 
    SkinModelRender::PreLoadModel("Assets/modelData/Balloon6.tkm");
    SkinModelRender::PreLoadModel("Assets/modelData/Balloon7.tkm");

    SkinModelRender::PreLoadModel("Assets/modelData/Needle.tkm");
    SkinModelRender::PreLoadModel("Assets/modelData/NeedleBoard.tkm");
    SkinModelRender::PreLoadModel("Assets/modelData/WindTurbineBase.tkm");
    SkinModelRender::PreLoadModel("Assets/modelData/WindTurbineBlades.tkm");

    SkinModelRender::PreLoadModel("Assets/modelData/SkyIsland.tkm");
    SkinModelRender::PreLoadModel("Assets/modelData/BuildingStage.tkm");
    SkinModelRender::PreLoadModel("Assets/modelData/TrapStage.tkm");
}