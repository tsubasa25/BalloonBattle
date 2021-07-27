#include "stdafx.h"
#include "GameScene.h"
#include "Player.h"
#include "BackGround.h"
#include "GameTimer.h"
#include "ResultScene.h"

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

    m_iniPlCount = m_playerCount;

    for (int i = 0; i < m_iniPlCount; i++)//�v���C���[�����
    {
        m_player[i] = NewGO<Player>(0,"player");
        m_player[i]->SetPlayerNum(i);//�v���C���[�ԍ���ݒ�
        //player[i]->SetIniPosition({ GetIniPos(i) });//�����ʒu��ݒ�
        m_player[i]->SetPlayerCount(m_playerCount);//�v���C���[�l����ݒ�
        m_player[i]->SetPlayerStock(m_stock);
        m_IsAlive[i] = true;//�����Ă��邱�Ƃɂ���
    }
    for (int i = 0; i < m_playerCount; i++)//�G������
    {
        for (int j = 0; j < m_playerCount; j++)
        {
            if (m_player[i]->GetPlayerNum() != m_player[j]->GetPlayerNum()) {//���������Ȃ��悤�ɂ���
                m_player[i]->SetEnemyData(m_player[j]);//�G��������
            }
        }
    }

    //�G�t�F�N�g�����p
   // eff.Init(u"Assets/effect/HitEff.efk");
    
    m_gameSceneState = GAME_STATE_LOOK_STAGE;

    m_gameStartFontRender = NewGO<FontRender>(1);
    m_gameStartFontRender->SetPosition({ -100.0f,0.0f });
    m_gameStartFontRender->SetScale(3.0f);
    m_gameStartFontRender->SetShadowFlag(true);
    m_gameStartFontRender->SetShadowOffset(4.0f);
    m_gameStartFontRender->SetShadowColor({0.0f,0.0f,0.0f,1.0f});

    GameTimer*gameTimer = NewGO<GameTimer>(0, "gameTimer");

    for (int i = 0; i < 4; i++) {
        m_button_Sprite[i] = NewGO<SpriteRender>(5);
    }
    m_button_Sprite[0]->Init("Assets/Image/LA.dds",192,108);
    m_button_Sprite[1]->Init("Assets/Image/LB.dds", 192, 108);
    m_button_Sprite[2]->Init("Assets/Image/B.dds", 192, 108);
    m_button_Sprite[3]->Init("Assets/Image/Y.dds", 192, 108);
    for (int i = 0; i < 4; i++) {
        m_button_Sprite[i]->SetPosition(m_buttonPos[i]);
    }
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
        Battle();
        m_isResult = false;
        break;
    case GAME_STATE_RESULT:
        if (m_isResult == false) {
            for (int i = 0; i < 4; i++)
            {
                if (m_button_Sprite[i] != nullptr)
                {
                    DeleteGO(m_button_Sprite[i]);
                }
            }
            m_isResult = true;
        }
        break;

    default:
        break;
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
}

void GameScene::LookStage()
{
    //�ŏ��̏���
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
        m_stageNameFontRender->SetShadowOffset(3.0f);
        m_stageNameFontRender->SetShadowColor({0.0f,0.0f,0.0f,1.0f});
    }
    //�X�e�[�W���̓���
    if (m_stageNamePos.x < -500.0f)
        m_stageNamePos.x += 40.0f;
    else if (m_stageNamePos.x < -350)
        m_stageNamePos.x += 1.0f;
    else 
        m_stageNamePos.x += 80.0f;

    m_stageNameFontRender->SetPosition(m_stageNamePos);

    //�J�����̓���
    Vector3 right = g_camera3D->GetRight();
    Vector3 cameraPos = g_camera3D->GetPosition();
    cameraPos += right * 40.0f;
    g_camera3D->SetPosition(cameraPos);

    //���̏�����
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
        m_gameStartFontRender->SetPosition({-180.0f, 50.0f});
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

void GameScene::Battle()
{
    m_alivePlCount = 0;
    QueryGOs<Player>("player", [this](Player* player)->bool {
        m_alivePlCount++;
        return true;
        });
    if (m_alivePlCount == 0)
    {
        SetGameState(GAME_STATE_RESULT);
        ResultScene* resultScene = NewGO<ResultScene>(0, "resultScene");
        resultScene->SetResultMode(resultScene->GetEnGameSet());
    }

}

void GameScene::SetIniPosition()
{
    m_gameSceneState = GAME_STATE_LOOK_STAGE;

    m_gameStartFontRender = NewGO<FontRender>(1);
    m_gameStartFontRender->SetPosition({ -100.0f,0.0f });
    m_gameStartFontRender->SetScale(3.0f);
    m_gameStartFontRender->SetShadowFlag(true);
    m_gameStartFontRender->SetShadowOffset(4.0f);
    m_gameStartFontRender->SetShadowColor({ 0.0f,0.0f,0.0f,1.0f });

    m_gameStartCallTimer = INI_GAME_START_CALL_TIME;
    m_lookStageTimer = INI_LOOK_STAGE_TIME;

    m_playerCount = m_iniPlCount;

    for (int i = 0; i < m_iniPlCount; i++)//�v���C���[�����
    {
        m_player[i] = NewGO<Player>(0, "player");
        m_player[i]->SetPlayerNum(i);//�v���C���[�ԍ���ݒ�
        //player[i]->SetIniPosition({ GetIniPos(i) });//�����ʒu��ݒ�
        m_player[i]->SetPlayerStock(m_stock);
        m_player[i]->SetPlayerCount(m_playerCount);//�v���C���[�l����ݒ�

        //m_IsAlive[i] = true;//�����Ă��邱�Ƃɂ���
    }
    for (int i = 0; i < m_playerCount; i++)//�G������
    {
        for (int j = 0; j < m_playerCount; j++)
        {
            if (m_player[i]->GetPlayerNum() != m_player[j]->GetPlayerNum()) {//���������Ȃ��悤�ɂ���
                m_player[i]->SetEnemyData(m_player[j]);//�G��������
            }
        }
    }
    NewGO<GameTimer>(0, "gameTimer");

    for (int i = 0; i < 4; i++) {
        m_button_Sprite[i] = NewGO<SpriteRender>(5);
    }
    m_button_Sprite[0]->Init("Assets/Image/LA.dds", 192, 108);
    m_button_Sprite[1]->Init("Assets/Image/LB.dds", 192, 108);
    m_button_Sprite[2]->Init("Assets/Image/B.dds", 192, 108);
    m_button_Sprite[3]->Init("Assets/Image/Y.dds", 192, 108);
    for (int i = 0; i < 4; i++) {
        m_button_Sprite[i]->SetPosition(m_buttonPos[i]);
    }
}
