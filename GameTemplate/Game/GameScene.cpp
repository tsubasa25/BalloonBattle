#include "stdafx.h"
#include "GameScene.h"
#include "Player.h"
GameScene::~GameScene()
{

}
bool GameScene::Start()
{
    for (int i = 0; i < m_playerCount; i++)//�v���C���[�����
    {
        player[i] = NewGO<Player>(0);
        player[i]->SetPlayerNum(i);//�v���C���[�ԍ���ݒ�
        player[i]->SetIniPosition({ GetIniPos(i) });//�����ʒu��ݒ�
        player[i]->SetPlayerCount(m_playerCount);//�v���C���[�l����ݒ�
    }
    for (int i = 0; i < m_playerCount; i++)//�G������
    {
        for (int j = 0; j < m_playerCount; j++)
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