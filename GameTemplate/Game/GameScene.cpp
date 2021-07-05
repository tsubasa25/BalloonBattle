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
        player[i] = NewGO<Player>(0,"player");
        player[i]->SetPlayerNum(i);//�v���C���[�ԍ���ݒ�
        //player[i]->SetIniPosition({ GetIniPos(i) });//�����ʒu��ݒ�
        player[i]->SetPlayerCount(m_playerCount);//�v���C���[�l����ݒ�

        m_IsAlive[i] = true;//�����Ă��邱�Ƃɂ���
    }
    for (int i = 0; i < m_playerCount; i++)//�G������
    {
        for (int j = 0; j < m_playerCount; j++)
        {
            if (player[i]->GetPlayerNum() != player[j]->GetPlayerNum()) {//���������Ȃ��悤�ɂ���
                player[i]->SetEnemyData(player[j]);//�G��������
            }
        }
    }

    //�G�t�F�N�g�����p
    //eff = NewGO<Effect>(0);
    eff.Init(u"Assets/effect/JetEff02.efk");
    


	return true;
}
void GameScene::Update()
{
    if (g_pad[0]->IsPress(enButtonRB1)&&aa==true) {//���C�g�̎���
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
    //if (g_pad[0]->IsTrigger(enButtonX)) {//����
    //    for (int i = 0; i < 8; i++)
    //    {
    //        if (m_IsAlive[i] == false) {
    //            player[i] = NewGO<Player>(0,"player");
    //            player[i]->SetPlayerNum(i);//�v���C���[�ԍ���ݒ�
    //            player[i]->SetIniPosition({ GetIniPos(i) });//�����ʒu��ݒ�
    //            m_playerCount++;//���v�l����ݒ�
    //            player[i]->SetPlayerCount(m_playerCount);//�v���C���[�l����ݒ�
    //            m_IsAlive[i] = true;//�����Ă��邱�Ƃɂ���
    //           
    //            for (int j = 0; j < m_playerCount; j++)//�G������
    //            {
    //                if (player[i]->GetPlayerNum() != player[j]->GetPlayerNum()) {//���������Ȃ��悤�ɂ���
    //                    player[i]->SetEnemyData(player[j]);//�G��������
    //                    player[j]->SetEnemyData(player[i]);//�G��������
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