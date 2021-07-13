#include "stdafx.h"
#include "BackGround.h"
#include "GameScene.h"
#include "Player.h"
#include "GimmickNeedle.h"
#include "Sky.h"

BackGround::~BackGround()
{
    DeleteGO(m_skinModelRender);
    DeleteGO(m_map1BGM);
    DeleteGO(m_map2BGM);
    DeleteGO(m_map3BGM);
}
bool BackGround::Start()
{

    m_sky = NewGO<Sky>(0);
    m_sky->Init(L"Assets/Image/skyMap/sky2.dds");
    m_sky->SetPosition({ 0,-5000,0 });
    
    m_skinModelRender = NewGO<SkinModelRender>(0, "backGround");
    //ステージは影を発生させる
    m_skinModelRender->SetShadowCasterFlag(false);
    
    switch (m_stageNum)
    {
    case 0://空島ステージ
        m_stageName = STAGE_ZERO_NAME;
        m_map1BGM = NewGO<SoundSource>(0);
        m_map1BGM->Init(L"Assets/sound/マップ1BGM.wav", SoundType::enBGM);
        m_map1BGM->SetVolume(SOUND_MAP_BGM_VOLUME);
        m_map1BGM->Play(true);
        m_skinModelRender->Init("Assets/modelData/SkyIsland.tkm");
        break;
    case 1://ビルステージ
        m_stageName = STAGE_ONE_NAME;
        m_map2BGM = NewGO<SoundSource>(0);
        m_map2BGM->Init(L"Assets/sound/マップ2BGM.wav", SoundType::enBGM);
        m_map2BGM->SetVolume(SOUND_MAP_BGM_VOLUME);
        m_map2BGM->Play(true);
        m_skinModelRender->Init("Assets/modelData/BuildingStage.tkm");     break;
    case 2://トラップステージ
        m_stageName = STAGE_TWO_NAME;
        m_map3BGM = NewGO<SoundSource>(0);
        m_map3BGM->Init(L"Assets/sound/マップ3BGM.wav", SoundType::enBGM);
        m_map3BGM->SetVolume(SOUND_MAP_BGM_VOLUME);
        m_map3BGM->Play(true);
        m_skinModelRender->Init("Assets/modelData/TrapStage.tkm");
    break;
    case 3://ランダムで決める
    {
        int randNum = 0;
        randNum = rand() % 3;
        switch (randNum)
        {
        case 0:
            m_skinModelRender->Init("Assets/modelData/SkyIsland.tkm");
            break;
        case 1:
            m_skinModelRender->Init("Assets/modelData/BuildingStage.tkm");
            break;
        case 2:
            m_skinModelRender->Init("Assets/modelData/TrapStage.tkm");
            break;
        default:
            break;
        }
        break;
    }
    default:
        break;
    
    }
   
     //ステージのモデルの静的物理モデルを作成        
    m_physicsStaticObject.CreateFromModel(m_skinModelRender->GetModel(), m_skinModelRender->GetModel().GetWorldMatrix());


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
            else if (strcmp(objData.name, "WTBasePoint")== 0)
            {
                if (m_stageNum == 0)
                {             
                    WindTurbine* windTurbine = NewGO<WindTurbine>(0, "windTurbine");
                    windTurbine->SetPosition(objData.position);                    
                }
                return true;
            }
            else if (strcmp(objData.name, "WTBladesPoint") == 0)
            {
                m_WTBladesPos = objData.position;
                return true;
            }
            else if (strcmp(objData.name, "NeedlePoint") == 0)
            {
                if (m_stageNum == 2)
                {
                    GimmickNeedle* gimmickNeedle = NewGO<GimmickNeedle>(0, "gimmickNeedle");
                    gimmickNeedle->SetPosition(objData.position);
                }        
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

//リスポーン地点を割り出す関数
Vector3 BackGround::GetRespawnPosition(int ResPlNum)
{
    m_respawnPlayerNum = ResPlNum;
    m_enemyMiddlePos = {Vector3::Zero};

    //まず、自分以外のプレイヤーのポジションを全員分加算
    QueryGOs<Player>("player", [this](Player* player)->bool 
        {
        if (player->GetPlayerNum() != m_respawnPlayerNum)
            m_enemyMiddlePos += player->GetPosition();     
        return true;
        });
    //そして自分以外のプレイヤー数で割ることで、平均位置を求める。
    m_enemyMiddlePos /= m_gameScene->GetPlayerCount() - 1.0f;

    Vector3 ResPos = { Vector3::Zero }; //リスポーン地点
    Vector3 toResPosDis = {Vector3::Zero};  //リスポーン地点からm_enemyMiddlePosへの距離
    Vector3 dis = { Vector3::Zero };    //リスポーン地点候補からm_enemyMiddlePosへの距離

    //リスポーン地点の候補から、m_enemyMiddlePosへの距離が最も遠い場所を割り出す。
    for (int i = 0; i < RESPAWN_POSITION_NUM; i++)
    {
        dis = m_spawnPos[i] - m_enemyMiddlePos;
        if (toResPosDis.Length() < dis.Length())
        {
            toResPosDis = dis;
            ResPos = m_spawnPos[i];
        }
    }

    //空中からリスポーンするようにする。
     ResPos.y += RESPAWN_POSITION_HEIGHT;
    
    return ResPos;
}

void BackGround::Retri()
{
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
}