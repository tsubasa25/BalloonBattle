#include "stdafx.h"
#include "WindTurbine.h"
WindTurbine::~WindTurbine()
{

}

bool WindTurbine::Start()
{
	m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->Init("Assets/modelData/WindTurbine.tkm");
	m_skinModelRender->SetPosition(m_position);

	return true;
}

void WindTurbine::Update()
{

}