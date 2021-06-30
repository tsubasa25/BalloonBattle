#include "stdafx.h" 
#include "system/system.h"
#include "Player.h"
#include "GameScene.h"
#include "BackGround.h"
#include "TitleScene.h"
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

    EffectEngine::CreateInstance();

    TitleScene* titleScene = NewGO<TitleScene>(0, "titleScene");
   /* GameScene*gameScene=NewGO<GameScene>(0,"gameScene");*/   
   /* NewGO<BackGround>(0);*/

    g_camera3D->SetPosition({ 0.0f, 1200.0f, -1800.0f });
    g_camera3D->SetTarget({ 0,0,-300 });    
    g_camera3D->SetFar(50000.0f);
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
