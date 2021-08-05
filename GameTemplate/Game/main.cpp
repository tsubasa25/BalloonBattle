#include "stdafx.h" 
#include "system/system.h"
#include "Player.h"
#include "GameScene.h"
#include "BackGround.h"
#include "TitleBack.h"
#include "TitleScene.h"
#include "RaceMode.h"
    namespace
    {
        const Vector3 LIGHTCAMERA_POSITION = { 0.0f, 2000.0f,0.0f };
        const Vector3 LIGHTCAMERA_TARGET = { 0,0,0 };
        const Vector3 LIGHTCAMERA_UP = { 1.0f,0.0f,0.0f };
        const float LIGHTCAMERA_WIDTH = 2000.0f;
        const float LIGHTCAMERA_HEIGHT = 2000.0f;
        const int CAMERA_FAR = 100000;
    }

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
        nsBalloon::LightManager::CreateInstance();
        nsBalloon::LightManager::GetInstance()->SetLightCameraPosition(LIGHTCAMERA_POSITION);
        nsBalloon::LightManager::GetInstance()->SetLightCameraTarget(LIGHTCAMERA_TARGET);
        nsBalloon::LightManager::GetInstance()->SetLightCameraUp(LIGHTCAMERA_UP);
        nsBalloon::LightManager::GetInstance()->SetLightCameraUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Perspective);

        //���\�[�X�}�l�[�W���̃C���X�^���X���쐬
        nsBalloon::ResourceBankManager::CreateInstance();

        // �T�E���h�G���W���̃C���X�^���X���쐬����B
        nsBalloon::SoundEngine::CreateInstance();
        nsBalloon::SoundEngine::GetInstance()->Init();

        EffectEngine::CreateInstance();

        nsBalloon::PostEffectManager::CreateInstance();
        //�u���[���t���O�A�V���h�E�t���O�̏���
        nsBalloon::PostEffectManager::GetInstance()->Init(true, true);
        //////////////////////////////////////////////////

        //FPS�Œ�p�X�g�b�v�E�H�b�`
        Stopwatch stopwatch;

        nsBalloon::TitleScene* titleScene = NewGO<nsBalloon::TitleScene>(0, "titleScene");//�^�C�g�����S�ESTART
        nsBalloon::TitleBack* titleBack = NewGO<nsBalloon::TitleBack>(0, "titleBack");//�����w�i

        //nsBalloon::RaceMode* raceMode = NewGO<nsBalloon::RaceMode>(0, "raceMode");



        g_camera3D->SetFar(CAMERA_FAR);
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


            nsBalloon::LightManager::GetInstance()->UpdateEyePos();

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
