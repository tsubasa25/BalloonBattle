#include "stdafx.h"
#include "GameScene.h"
#include "Player.h"
GameScene::~GameScene()
{

}
bool GameScene::Start()
{
    for (int i = 0; i < 4; i++)//�v���C���[�����
    {
        player[i] = NewGO<Player>(0);
        player[i]->SetPlayerNum(i);//�v���C���[�ԍ���ݒ�
        player[i]->SetIniPosition({ GetIniPos(i) });//�����ʒu��ݒ�
    }
    for (int i = 0; i < 4; i++)//�G������
    {
        for (int j = 0; j < 4; j++)
        {
            if (player[i]->GetPlayerNum() != player[j]->GetPlayerNum()) {//���������Ȃ��悤�ɂ���
                player[i]->m_enemy.push_back(player[j]);//�G�������� 
            }
        }
        //m_enemyNum = 0;
    }
    
	return true;
}
void GameScene::Update()
{

}