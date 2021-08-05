#include "stdafx.h"
#include "BackGroundForRace.h"
namespace nsBalloon {
	BackGroundForRace::~BackGroundForRace()
	{

	}
	bool BackGroundForRace::Start()
	{
		m_skinModelRender = NewGO<SkinModelRender>(0);
		m_skinModelRender->Init("Assets/modelData/RaseStage.tkm");
		return true;
	}
	void BackGroundForRace::Update()
	{

	}
}