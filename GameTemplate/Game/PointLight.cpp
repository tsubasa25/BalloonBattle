#include "stdafx.h"
#include "PointLight.h"
//ポイントライトの数を減らした時
PointLight::~PointLight()
{

}
PointLight::PointLight()
{
	m_pointLigData = LightManager::GetInstance()->GetPointLigData();
	LightManager::GetInstance()->AddPointLigNum(LightManager::GetInstance()->GetPointLigNum());
}
//ポイントライトの数を増やした時
bool PointLight::Start()
{
	
	return true;
}

//毎フレームカメラの位置とポイントライトのデータを更新
void PointLight::Update()
{
	LightManager::GetInstance()->UpdatePointLight(LightManager::GetInstance()->GetPointLigNum());
}