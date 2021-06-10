#include "stdafx.h"
#include "system/system.h"
#include "Player.h"
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

    /*SkinModelRender* skinModelRender = NewGO<SkinModelRender>(0);
    skinModelRender->Init("Assets/modelData/Ballon.tkm");
    skinModelRender->SetPosition({ 0,500,-100 });
    skinModelRender->SetScale({ 0.5,0.5, 0.5 });
    SkinModelRender* unityChan = NewGO<SkinModelRender>(0);
    unityChan->Init("Assets/modelData/unityChan.tkm");
    unityChan->SetPosition({ 50,0,-100 });*/
    SkinModelRender* Stage = NewGO<SkinModelRender>(0);
    //Stage->Init("Assets/modelData/bg/bg.tkm");
    Stage->Init("Assets/modelData/Stage.tkm");
    //skinModelRender->SetScale({ 0.5,0.5, 0.5 });
    DirectionLight* directionLight = nullptr;
    directionLight = NewGO<DirectionLight>(0);
    directionLight->SetColor({ 1,1,1 });
    directionLight->SetDirection({ 0,-1,-1 });
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
    //skinModelRender->SetPosition({ Vector3::Zero });
    g_camera3D->SetPosition({ 0.0f, 500.0f, 500.0f });
    g_camera3D->SetTarget({ 0,50,0 });
    Vector3 LightPos;
    LightPos.y += 50;


    Player* player0 = NewGO<Player>(0);
    player0->SetPlayerNum(0);
    Player* player1 = NewGO<Player>(0);
    player1->SetPlayerNum(1);
    
   
    
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
        //Stage->Render(renderContext);
        //skinModelRender->Render(renderContext);
        //unityChan->Render(renderContext);
        //////////////////////////////////////
        // ここから絵を描くコードを記述する
        //////////////////////////////////////
        Vector3 position;
       
        position.x -= g_pad[0]->GetRStickXF() * 2;
        position.z -= g_pad[0]->GetRStickYF() * 2;
        LightPos += position;
        
        //skinModelRender->SetPosition({ LightPos });
        LightManager::GetInstance()->UpdateEyePos();
        //////////////////////////////////////
        // 絵を描くコードを書くのはここまで！！！
        //////////////////////////////////////
        // レンダリング終了
        g_engine->EndFrame();
    }
    return 0;
}
