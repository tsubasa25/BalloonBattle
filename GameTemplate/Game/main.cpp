#include "stdafx.h" 
#include "system/system.h"
#include "Player.h"
#include "GameScene.h"
#include "BackGround.h"
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
    // 初期化を行うコードを書くのはここまで！！！
    //////////////////////////////////////
    auto& renderContext = g_graphicsEngine->GetRenderContext();

    // ここからゲームループ
    while (DispatchWindowMessage())
    {
        // レンダリング開始
        g_engine->BeginFrame();
        GameObjectManager::GetInstance()->ExecuteUpdate();
        GameObjectManager::GetInstance()->ExecuteRender(renderContext);
       
        //////////////////////////////////////
        // ここから絵を描くコードを記述する
        //////////////////////////////////////
       
        
        LightManager::GetInstance()->UpdateEyePos();
        //////////////////////////////////////
        // 絵を描くコードを書くのはここまで！！！
        //////////////////////////////////////
        // レンダリング終了
        g_engine->EndFrame();
    }
    return 0;
}
