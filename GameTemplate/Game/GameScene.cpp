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
        player[i] = NewGO<Player>(0);
        player[i]->SetPlayerNum(i);//プレイヤー番号を設定
        player[i]->SetIniPosition({ GetIniPos(i) });//初期位置を設定
        player[i]->SetPlayerCount(m_playerCount);//プレイヤー人数を設定
    }
    for (int i = 0; i < m_playerCount; i++)//敵を入れる
    {
        for (int j = 0; j < m_playerCount; j++)
        {
            if (player[i]->GetPlayerNum() != player[j]->GetPlayerNum()) {//自分を入れないようにする
                player[i]->m_enemy.push_back(player[j]);//敵情報を入れる 
            }
        }
        //m_enemyNum = 0;
    }
    
	return true;
}
void GameScene::Update()
{

}