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
    if (g_pad[0]->IsPress(enButtonRB1)&&aa==true) {
        for (int i = 0; i < 10; i++) {
            pointLight[i] = NewGO<PointLight>(0);
            pointLight[i]->SetColor({ 10,0,0 });
            pointLight[i]->SetPosition({ 0,10,0 });
            pointLight[i]->SetRange(100);
        }
        aaNum = 0;
        aa = false;
    }
    if (g_pad[0]->IsPress(enButtonLB1)&& aa==false) {
        DeleteGO(pointLight[aaNum]);
        aaNum++;
        if (aaNum > 9) {
            aa = true;
        }
    }
}