#include "stdafx.h"
#include "BackGround.h"

BackGround::~BackGround()
{
    DeleteGO(m_skinModelRender);
    DeleteGO(m_directionLight);
}
bool BackGround::Start()
{
    m_skinModelRender = NewGO<SkinModelRender>(0);
    m_skinModelRender->Init("Assets/modelData/TestStage.tkm"); 

    //ステージのモデルの静的物理モデルを作成
    m_physicsStaticObject.CreateFromModel(m_skinModelRender->GetModel(), m_skinModelRender->GetModel().GetWorldMatrix());

    m_directionLight = nullptr;
    m_directionLight = NewGO<DirectionLight>(0);
    m_directionLight->SetColor({ 0.7f,0.7f,0.7f });
    m_directionLight->SetDirection({ -2,-1,-1 });

   

    m_level.Init("Assets/modelData/Level/Level00.tkl", [&](LevelObjectData& objData)
        {
            if (strcmp(objData.name, "TestPos") == 0) {        
                //風車を表示
                m_windTurbine = NewGO<WindTurbine>(0);
                m_windTurbine->SetPosition(objData.position);

                return true;
            }
            return false;
        });

	return true;
}
void BackGround::Update()
{

}