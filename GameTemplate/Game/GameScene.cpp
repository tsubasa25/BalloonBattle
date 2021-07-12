#include "stdafx.h"
#include "GameScene.h"
#include "Player.h"
#include "BackGround.h"
GameScene::~GameScene()
{
    DeleteGO(m_directionLight);
}
bool GameScene::Start()
{
    m_directionLight = nullptr;
    m_directionLight = NewGO<DirectionLight>(0);
    m_directionLight->SetColor({ 1.0f,1.0f,1.0f });
    m_directionLight->SetDirection({ -1.0f, -1.0f, 0.5f });

    for (int i = 0; i < m_playerCount; i++)//プレイヤーを作る
    {
        player[i] = NewGO<Player>(0,"player");
        player[i]->SetPlayerNum(i);//プレイヤー番号を設定
        //player[i]->SetIniPosition({ GetIniPos(i) });//初期位置を設定
        player[i]->SetPlayerCount(m_playerCount);//プレイヤー人数を設定
        player[i]->SetPlayerStock(m_stock);
        m_IsAlive[i] = true;//生きていることにする
    }
    for (int i = 0; i < m_playerCount; i++)//敵を入れる
    {
        for (int j = 0; j < m_playerCount; j++)
        {
            if (player[i]->GetPlayerNum() != player[j]->GetPlayerNum()) {//自分を入れないようにする
                player[i]->SetEnemyData(player[j]);//敵情報を入れる
            }
        }
    }

    //エフェクト実験用
   // eff.Init(u"Assets/effect/HitEff.efk");
    
    m_gameSceneState = GAME_STATE_LOOK_STAGE;

    m_gameStartFontRender = NewGO<FontRender>(1);
    m_gameStartFontRender->SetPosition({ -100.0f,0.0f });
    m_gameStartFontRender->SetScale(3.0f);
    m_gameStartFontRender->SetShadowFlag(true);
    m_gameStartFontRender->SetShadowColor({0.0f,0.0f,0.0f,1.0f});

	return true;
}
void GameScene::Update()
{
    switch (m_gameSceneState)
    {
    case GAME_STATE_LOOK_STAGE:
        LookStage();
        break;

    case GAME_STATE_START_CALL:
        GameStartCall();
        break;

    case GAME_STATE_BATTLE:
        break;

    default:
        break;
    }

    if (g_pad[0]->IsPress(enButtonRB1)&&aa==true) {//ライトの実験
        for (int i = 0; i < 10; i++) {
            pointLight[i] = NewGO<PointLight>(0);
            pointLight[i]->SetColor({ 10,0,0 });
            pointLight[i]->SetPosition({ 0,10,0 });
            pointLight[i]->SetRange(100);
        }
        aaNum = 9;
        aa = false;
    }
    if (g_pad[0]->IsPress(enButtonLB1)&& aa==false) {
        DeleteGO(pointLight[aaNum]);
        aaNum--;
        if (aaNum <0) {
            aa = true;
        }
    }
    //if (g_pad[0]->IsTrigger(enButtonX)) {//復活
    //    for (int i = 0; i < 8; i++)
    //    {
    //        if (m_IsAlive[i] == false) {
    //            player[i] = NewGO<Player>(0,"player");
    //            player[i]->SetPlayerNum(i);//プレイヤー番号を設定
    //            player[i]->SetIniPosition({ GetIniPos(i) });//初期位置を設定
    //            m_playerCount++;//合計人数を設定
    //            player[i]->SetPlayerCount(m_playerCount);//プレイヤー人数を設定
    //            m_IsAlive[i] = true;//生きていることにする
    //           
    //            for (int j = 0; j < m_playerCount; j++)//敵を入れる
    //            {
    //                if (player[i]->GetPlayerNum() != player[j]->GetPlayerNum()) {//自分を入れないようにする
    //                    player[i]->SetEnemyData(player[j]);//敵情報を入れる
    //                    player[j]->SetEnemyData(player[i]);//敵情報を入れる
    //                }
    //            }
    //            break;
    //        }
    //    }
    //}

    if (g_pad[0]->IsTrigger(enButtonLB2))
    {
       /* eff.Play();
        eff.SetPosition({ 0.0f,50.0f,0.0f });
        eff.SetScale({30.0f, 30.0f, 30.0f});
        eff.Update();*/
    }
    
}

void GameScene::LookStage()
{
    //最初の処理
    if (m_lookStageTimer == INI_LOOK_STAGE_TIME)
    {
        g_camera3D->SetPosition({ -4000.0f,500.0f,0.0f });

        m_stageNameFontRender = NewGO<FontRender>(1);

        BackGround* backGround = FindGO<BackGround>("backGround");
        std::wstring stageName = backGround->GetStageName();
        m_stageNameFontRender->SetText(stageName);
        m_stageNamePos = { -1800.0f,-200.0f };
        m_stageNameFontRender->SetPosition(m_stageNamePos);
        m_stageNameFontRender->SetScale(1.5f);
        m_stageNameFontRender->SetShadowFlag(true);
        m_stageNameFontRender->SetShadowColor({0.0f,0.0f,0.0f,1.0f});
    }
    //ステージ名の動き
    if (m_stageNamePos.x < -500.0f)
        m_stageNamePos.x += 40.0f;
    else if (m_stageNamePos.x < -350)
        m_stageNamePos.x += 1.0f;
    else 
        m_stageNamePos.x += 80.0f;

    m_stageNameFontRender->SetPosition(m_stageNamePos);

    //カメラの動き
    Vector3 right = g_camera3D->GetRight();
    Vector3 cameraPos = g_camera3D->GetPosition();
    cameraPos += right * 40.0f;
    g_camera3D->SetPosition(cameraPos);

    //次の処理へ
    if (g_pad[0]->IsTrigger(enButtonA) || m_lookStageTimer <= 0)
    {
        DeleteGO(m_stageNameFontRender);
        m_gameSceneState = GAME_STATE_START_CALL;
        g_camera3D->SetPosition(INI_CAMERA_POS);
        g_camera3D->SetTarget(INI_CAMERA_TARGET_POS);
    }
    m_lookStageTimer--;
}

void GameScene::GameStartCall()
{
   
    if (m_gameStartCallTimer == INI_GAME_START_CALL_TIME)
    {
        m_gameStartFontRender->SetText(L"READY");
        m_gameStartFontRender->SetPosition({-200.0f, 50.0f});
    }
    else if (m_gameStartCallTimer == 50)
    {
        m_gameStartFontRender->SetText(L"GO!!");
        m_gameStartFontRender->SetPosition({ -150.0f, 50.0f });
    }
    else if(m_gameStartCallTimer <= 0)
    {
        QueryGOs<Player>("player", [this](Player* player)->bool {
            player->SetCanMove(true);
            return true;
            });
        m_gameSceneState = GAME_STATE_BATTLE;
        DeleteGO(m_gameStartFontRender);
    }
        m_gameStartCallTimer--;
}

void GameScene::Retri()
{
    m_gameSceneState = GAME_STATE_LOOK_STAGE;

    m_gameStartFontRender = NewGO<FontRender>(1);
    m_gameStartFontRender->SetPosition({ -100.0f,0.0f });
    m_gameStartFontRender->SetScale(3.0f);
    m_gameStartFontRender->SetShadowFlag(true);
    m_gameStartFontRender->SetShadowColor({ 0.0f,0.0f,0.0f,1.0f });

    m_gameStartCallTimer = INI_GAME_START_CALL_TIME;
    m_lookStageTimer = INI_LOOK_STAGE_TIME;

    for (int i = 0; i < m_playerCount; i++)//プレイヤーを作る
    {
        player[i] = NewGO<Player>(0, "player");
        player[i]->SetPlayerNum(i);//プレイヤー番号を設定
        //player[i]->SetIniPosition({ GetIniPos(i) });//初期位置を設定
        player[i]->SetPlayerCount(m_playerCount);//プレイヤー人数を設定

        //m_IsAlive[i] = true;//生きていることにする
    }
    for (int i = 0; i < m_playerCount; i++)//敵を入れる
    {
        for (int j = 0; j < m_playerCount; j++)
        {
            if (player[i]->GetPlayerNum() != player[j]->GetPlayerNum()) {//自分を入れないようにする
                player[i]->SetEnemyData(player[j]);//敵情報を入れる
            }
        }
    }
}
