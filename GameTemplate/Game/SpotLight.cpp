#include "stdafx.h"
#include "SpotLight.h"
namespace nsBalloon {
	//スポットライトの数を減らした時
	SpotLight::~SpotLight()
	{
	}
	SpotLight::SpotLight()
	{
		m_spotLigData = LightManager::GetInstance()->GetSpotLigData();
		LightManager::GetInstance()->AddSpotLigNum(LightManager::GetInstance()->GetSpotLigNum());
	}

	//スポットライトの数を増やした時
	bool SpotLight::Start()
	{

		return true;
	}

	//毎フレームカメラの位置とスポットライトのデータを更新
	void SpotLight::Update()
	{
		LightManager::GetInstance()->UpdateSpotLight(LightManager::GetInstance()->GetSpotLigNum());
	}
}