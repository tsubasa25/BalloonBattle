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
    m_skinModelRender->Init("Assets/modelData/SimpleStage.tkm");

    //ステージのモデルの静的物理モデルを作成
    m_physicsStaticObject.CreateFromModel(m_skinModelRender->GetModel(), m_skinModelRender->GetModel().GetWorldMatrix());

    m_directionLight = nullptr;
    m_directionLight = NewGO<DirectionLight>(0);
    m_directionLight->SetColor({ 0.7f,0.7f,0.7f });
    m_directionLight->SetDirection({ -2,-1,-1 });

    m_gameScene = FindGO<GameScene>("gameScene");


    m_level.Init("Assets/modelData/Level/SimpleLevel.tkl", [&](LevelObjectData& objData)
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