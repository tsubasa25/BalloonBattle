#include "stdafx.h"
#include "PointLight.h"
//�|�C���g���C�g�̐������炵����
PointLight::~PointLight()
{

}
PointLight::PointLight()
{
	m_pointLigData = LightManager::GetInstance()->GetPointLigData();
	LightManager::GetInstance()->AddPointLigNum(LightManager::GetInstance()->GetPointLigNum());
}
//�|�C���g���C�g�̐��𑝂₵����
bool PointLight::Start()
{
	
	return true;
}

//���t���[���J�����̈ʒu�ƃ|�C���g���C�g�̃f�[�^���X�V
void PointLight::Update()
{
	LightManager::GetInstance()->UpdatePointLight(LightManager::GetInstance()->GetPointLigNum());
}