#include "stdafx.h"
#include "GameScene.h"
#include "Player.h"
GameScene::~GameScene()
{

}
bool GameScene::Start()
{
    for (int i = 0; i < 4; i++)//プレイヤーを作る
    {
        player[i] = NewGO<Player>(0);
        player[i]->SetPlayerNum(i);//プレイヤー番号を設定
        player[i]->SetIniPosition({ GetIniPos(i) });//初期位置を設定
    }
    for (int i = 0; i < 4; i++)//敵を入れる
    {
        for (int j = 0; j < 4; j++)
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