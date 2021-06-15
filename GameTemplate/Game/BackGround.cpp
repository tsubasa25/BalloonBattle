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

    m_skinModelRender->Init("Assets/modelData/Stage.tkm"); 
    //ステージのモデルの静的物理モデルを作成
    m_physicsStaticObject.CreateFromModel(m_skinModelRender->GetModel(), m_skinModelRender->GetModel().GetWorldMatrix());

    m_directionLight = nullptr;
    m_directionLight = NewGO<DirectionLight>(0);
    m_directionLight->SetColor({ 1,1,1 });
    m_directionLight->SetDirection({ 0,-1,-1 });
	return true;
}
void BackGround::Update()
{

}