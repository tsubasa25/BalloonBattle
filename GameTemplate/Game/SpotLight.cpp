#include "stdafx.h"
#include "SpotLight.h"
namespace nsBalloon {
	//�X�|�b�g���C�g�̐������炵����
	SpotLight::~SpotLight()
	{
	}
	SpotLight::SpotLight()
	{
		m_spotLigData = LightManager::GetInstance()->GetSpotLigData();
		LightManager::GetInstance()->AddSpotLigNum(LightManager::GetInstance()->GetSpotLigNum());
	}

	//�X�|�b�g���C�g�̐��𑝂₵����
	bool SpotLight::Start()
	{

		return true;
	}

	//���t���[���J�����̈ʒu�ƃX�|�b�g���C�g�̃f�[�^���X�V
	void SpotLight::Update()
	{
		LightManager::GetInstance()->UpdateSpotLight(LightManager::GetInstance()->GetSpotLigNum());
	}
}