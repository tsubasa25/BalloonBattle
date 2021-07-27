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
    const int CAMERA_FAR = 100000;
}

///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    // ゲームの初期化
    InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

    //////////////////////////////////////
    // ここから初期化を行うコードを記述する
    //////////////////////////////////////

    //ゲームオブジェクトマネージャーのインスタンスを作成する。
    GameObjectManager::CreateInstance();
    PhysicsWorld::CreateInstance();
    //ライトマネージャーのインスタンスを作成
    LightManager::CreateInstance();
    LightManager::GetInstance()->SetLightCameraPosition(LIGHTCAMERA_POSITION);
    LightManager::GetInstance()->SetLightCameraTarget(LIGHTCAMERA_TARGET);
    LightManager::GetInstance()->SetLightCameraUp(LIGHTCAMERA_UP);
    LightManager::GetInstance()->SetLightCameraUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Perspective);
   
    //リソースマネージャのインスタンスを作成
    ResourceBankManager::CreateInstance();

    // サウンドエンジンのインスタンスを作成する。
    SoundEngine::CreateInstance();
    SoundEngine::GetInstance()->Init();

    EffectEngine::CreateInstance();

    PostEffectManager::CreateInstance();
    //ブルームフラグ、シャドウフラグの順番
    PostEffectManager::GetInstance()->Init(true, true);
    //////////////////////////////////////////////////

    //FPS固定用ストップウォッチ
    Stopwatch stopwatch;

    TitleScene* titleScene = NewGO<TitleScene>(0, "titleScene");//タイトルロゴ・START
    TitleBack* titleBack = NewGO<TitleBack>(0, "titleBack");//動く背景
  
    g_camera3D->SetFar(CAMERA_FAR);
    //////////////////////////////////////
    // 初期化を行うコードを書くのはここまで！！！
    //////////////////////////////////////
    auto& renderContext = g_graphicsEngine->GetRenderContext();

    // ここからゲームループ
    while (DispatchWindowMessage())
    {
        //FPS計測用ストップウォッチの計測開始
        stopwatch.Start();

        // レンダリング開始
        g_engine->BeginFrame();
      
        
        GameObjectManager::GetInstance()->ExecuteUpdate();
        GameObjectManager::GetInstance()->ExecuteRender(renderContext);
        //PostRenderはスプライト、フォント等、エフェクトを受けないものを描画する
        GameObjectManager::GetInstance()->ExecutePostRender(renderContext);
        
        //////////////////////////////////////
        // ここから絵を描くコードを記述する
        //////////////////////////////////////
       
        
        LightManager::GetInstance()->UpdateEyePos();
       
        EffectEngine::GetInstance()->Update(g_gameTime->GetFrameDeltaTime());
        EffectEngine::GetInstance()->Draw();
        //////////////////////////////////////
        // 絵を描くコードを書くのはここまで！！！
        //////////////////////////////////////
        // レンダリング終了
        g_engine->EndFrame();
    }
    return 0;
}
