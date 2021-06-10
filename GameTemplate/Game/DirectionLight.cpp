#include "stdafx.h"
#include "DirectionLight.h"
DirectionLight::~DirectionLight()
{

}
DirectionLight::DirectionLight()
{
	m_dirLigData=LightManager::GetInstance()->GetDirLigData();
	LightManager::GetInstance()->AddDirectionLigNum(LightManager::GetInstance()->GetDirectionLigNum());
}
bool DirectionLight::Start()
{	
	return true;
}
void DirectionLight::Update()
{	
	LightManager::GetInstance()->UpdateDirctionLight(LightManager::GetInstance()->GetDirectionLigNum());
}