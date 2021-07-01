#include "stdafx.h"
#include "BackGround.h"
#include "GameScene.h"
#include "Player.h"

BackGround::~BackGround()
{
    DeleteGO(m_skinModelRender);
    DeleteGO(m_directionLight);
}
bool BackGround::Start()
{
    m_skinModelRender = NewGO<SkinModelRender>(0, "backGround");
    m_skinModelRender->Init("Assets/modelData/BuildingStage.tkm");
    //�X�e�[�W�̃��f���̐ÓI�������f�����쐬    
    m_physicsStaticObject.CreateFromModel(m_skinModelRender->GetModel(), m_skinModelRender->GetModel().GetWorldMatrix());

    m_directionLight = nullptr;
    m_directionLight = NewGO<DirectionLight>(0);
    m_directionLight->SetColor({ 1.0f,1.0f,1.0f });
    m_directionLight->SetDirection({ -2,-1,-1 });

    m_gameScene = FindGO<GameScene>("gameScene");


    m_level.Init("Assets/modelData/Level/Level00.tkl", [&](LevelObjectData& objData)
        {             
            if (strcmp(objData.name, "SpawnP0") == 0)
            {
                m_spawnPos[0] = objData.position;
                return true;
            }
            else if (strcmp(objData.name, "SpawnP1") == 0)
            {
                m_spawnPos[1] = objData.position;
                return true;
            }
            else if (strcmp(objData.name, "SpawnP2") == 0)
            {
                m_spawnPos[2] = objData.position;
                return true;
            }
            else if (strcmp(objData.name, "SpawnP3") == 0)
            {
                m_spawnPos[3] = objData.position;
                return true;
            }
            else if (strcmp(objData.name, "SpawnP4") == 0)
            {
                m_spawnPos[4] = objData.position;
                return true;
            }
            else if (strcmp(objData.name, "SpawnP5") == 0)
            {
                m_spawnPos[5] = objData.position;
                return true;
            }
            else if (strcmp(objData.name, "SpawnP6") == 0)
            {
                m_spawnPos[6] = objData.position;
                return true;
            }
            else if (strcmp(objData.name, "SpawnP7") == 0)
            {
                m_spawnPos[7] = objData.position;
                return true;
            }
            else
            {
                return true;
            }               

            return false;
        });
        QueryGOs<Player>("player", [this](Player* player)->bool {
            switch (player->GetPlayerNum())
            {
            case 0:
                player->SetIniPosition(m_spawnPos[0]);
                break;
            case 1:
                player->SetIniPosition(m_spawnPos[1]);
                break;
            case 2:
                player->SetIniPosition(m_spawnPos[2]);
                break;
            case 3:
                player->SetIniPosition(m_spawnPos[3]);
                break;
            case 4:
                player->SetIniPosition(m_spawnPos[4]);
                break;
            case 5:
                player->SetIniPosition(m_spawnPos[5]);
                break;
            case 6:
                player->SetIniPosition(m_spawnPos[6]);
                break;
            case 7:
                player->SetIniPosition(m_spawnPos[7]);
                break;
            default:
                break;
            }
        return true;
        });

	return true;
}
void BackGround::Update()
{

}

//Vector3 BackGround::GetIniSpawnPosition()
//{
//
//
//    return 
//}

//���X�|�[���n�_������o���֐�
Vector3 BackGround::GetRespawnPosition(int ResPlNum)
{
    m_respawnPlayerNum = ResPlNum;
    m_enemyMiddlePos = {Vector3::Zero};

    //�܂��A�����ȊO�̃v���C���[�̃|�W�V������S�������Z
    QueryGOs<Player>("player", [this](Player* player)->bool 
        {
        if (player->GetPlayerNum() != m_respawnPlayerNum)
            m_enemyMiddlePos += player->GetPosition();     
        return true;
        });
    //�����Ď����ȊO�̃v���C���[���Ŋ��邱�ƂŁA���ψʒu�����߂�B
    m_enemyMiddlePos /= m_gameScene->GetPlayerCount() - 1.0f;

    Vector3 ResPos = { Vector3::Zero }; //���X�|�[���n�_
    Vector3 toResPosDis = {Vector3::Zero};  //���X�|�[���n�_����m_enemyMiddlePos�ւ̋���
    Vector3 dis = { Vector3::Zero };    //���X�|�[���n�_��₩��m_enemyMiddlePos�ւ̋���

    //���X�|�[���n�_�̌�₩��Am_enemyMiddlePos�ւ̋������ł������ꏊ������o���B
    for (int i = 0; i < RESPAWN_POSITION_NUM; i++)
    {
        dis = m_spawnPos[i] - m_enemyMiddlePos;
        if (toResPosDis.Length() < dis.Length())
        {
            toResPosDis = dis;
            ResPos = m_spawnPos[i];
        }
    }

    //�󒆂��烊�X�|�[������悤�ɂ���B
     ResPos.y += RESPAWN_POSITION_HEIGHT;
    
    return ResPos;
}