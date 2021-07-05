#include "stdafx.h"
#include "GameScene.h"
#include "Player.h"
GameScene::~GameScene()
{

}
bool GameScene::Start()
{
    for (int i = 0; i < m_playerCount; i++)//プレイヤーを作る
    {
        player[i] = NewGO<Player>(0,"player");
        player[i]->SetPlayerNum(i);//プレイヤー番号を設定
        //player[i]->SetIniPosition({ GetIniPos(i) });//初期位置を設定
        player[i]->SetPlayerCount(m_playerCount);//プレイヤー人数を設定

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
    //eff = NewGO<Effect>(0);
    eff.Init(u"Assets/effect/JetEff02.efk");
    


	return true;
}
void GameScene::Update()
{
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
        eff.Play();
        eff.SetPosition({ 0.0f,50.0f,0.0f });
        eff.SetScale({30.0f, 30.0f, 30.0f});
        eff.Update();
    }
    
}