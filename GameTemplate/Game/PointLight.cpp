#include "stdafx.h"
#include "PointLight.h"
//�|�C���g���C�g�̐������炵����
PointLight::~PointLight()
{
	LightManager::GetInstance()->RemovePointLight(m_pointLigData->pointLigNum);	
}
PointLight::PointLight()//�|�C���g���C�g�̐��𑝂₵����
{	
	m_pointLigData = LightManager::GetInstance()->GetPointLigData();//�f�[�^���m�ۂ���
	//m_pointLigData->pointLigNum = LightManager::GetInstance()->GetPointLigNum();//���ꂽ�ԍ����L�^����
	LightManager::GetInstance()->AddPointLig(GetLigData());//
}

bool PointLight::Start()
{
	
	return true;
}

//���t���[���J�����̈ʒu�ƃ|�C���g���C�g�̃f�[�^���X�V
void PointLight::Update()
{
	LightManager::GetInstance()->UpdatePointLight(m_pointLigData->pointLigNum,GetLigData());
}