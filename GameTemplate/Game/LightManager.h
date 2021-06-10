#pragma once
#include <array>
#include "stdafx.h"
#include "DirectionLight.h"
#include "PointLight.h"
#include "SpotLight.h"

namespace
{
	//�e���C�g�̍ő吔�@���̐���model.fx�̃��C�g�z��̐��ƈꏏ�ɂ��Ȃ���΂Ȃ�Ȃ�	
	const int DIRLIGHT_NUMBER_MAX = 5;
	const int POINTLIGHT_NUMBER_MAX = 20;
	const int SPOTLIGHT_NUMBER_MAX = 20;
}

class LightManager
{
private:
	LightManager() = default;
	~LightManager() = default;
	
	//���C�g�̏��ƃJ�����̈ʒu
	struct LigDatas
	{
		DirLigData directionLight[DIRLIGHT_NUMBER_MAX];		
		PointLigData pointLight[POINTLIGHT_NUMBER_MAX];
		SpotLigData spotLight[SPOTLIGHT_NUMBER_MAX];
		Vector3 eyePos;
		int dirctionLightNum = 0;
		int pointLightNum = 0;											//�|�C���g���C�g�̐�
		int spotLightNum = 0;
	};
	LigDatas m_ligData;				//���C�g�̃f�[�^
	int m_size = sizeof(m_ligData);	//���C�g�̃f�[�^�̃T�C�Y

	int m_dirctionLigCreateNum=0;//���Ԗڂɍ�������L�^
	int m_pointLigCreateNum=0;
	int m_spotLightCreateNum=0;

public:

	static LightManager* m_instance;

	/**
	 * @brief ���C�g�}�l�[�W���[�̃C���X�^���X���쐬����
	*/
	static void CreateInstance()
	{
		if (!m_instance)
		{
			m_instance = new LightManager;
		}
	}

	/**
	 * @brief ���C�g�}�l�[�W���[�̃C���X�^���X���폜����
	*/
	static void DeleteInstance()
	{
		delete m_instance;
		m_instance = nullptr;
	}

	/**
	 * @brief ���C�g�}�l�[�W���[�̃C���X�^���X���擾����
	*/
	static LightManager* GetInstance() { return m_instance; }
	/**
	 * @brief ���C�g�̃f�[�^�̉���擾����(�萔�o�b�t�@�ɓn���p)
	 * @return �S���C�g�̃f�[�^
	*/

	LigDatas* GetLigDatas() { return &m_ligData; }

	/**
	 * @brief ���C�g�̃f�[�^�̉�̃T�C�Y���擾����(�萔�o�b�t�@�ɓn���p)
	 * @return �S���C�g�̃f�[�^�̃T�C�Y
	*/
	int GetLigDataSize() { return m_size; }

	/**
	 * @brief �J�����̃|�W�V�������X�V����
	 * @param �J�����̔ԍ�
	*/
	void UpdateEyePos() { m_ligData.eyePos = g_camera3D->GetPosition(); }

	int GetDirectionLigNum() { return m_ligData.dirctionLightNum; }
	int GetPointLigNum() { return m_ligData.pointLightNum; }
	int GetSpotLigNum() { return m_ligData.spotLightNum; }


	void AddDirectionLigNum(int num) { m_ligData.dirctionLightNum = num + 1; }
	void AddPointLigNum(int num) { m_ligData.pointLightNum=num+1; }
	void AddSpotLigNum(int num) { m_ligData.spotLightNum=num+1; }

	void UpdateDirctionLight(int num) { m_ligData.dirctionLightNum = num; }
	void UpdatePointLight(int num) { m_ligData.pointLightNum = num; }
	void UpdateSpotLight(int num) { m_ligData.spotLightNum = num; }


	DirLigData* GetDirLigData() { return &m_ligData.directionLight[GetDirectionLigNum()]; }
	PointLigData* GetPointLigData() { return &m_ligData.pointLight[GetPointLigNum()]; }
	SpotLigData* GetSpotLigData() { return &m_ligData.spotLight[GetSpotLigNum()]; }
	
};