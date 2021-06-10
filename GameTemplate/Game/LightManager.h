#pragma once
#include <array>
#include "stdafx.h"
#include "DirectionLight.h"
#include "PointLight.h"
#include "SpotLight.h"

namespace
{
	//各ライトの最大数　この数はmodel.fxのライト配列の数と一緒にしなければならない	
	const int DIRLIGHT_NUMBER_MAX = 5;
	const int POINTLIGHT_NUMBER_MAX = 20;
	const int SPOTLIGHT_NUMBER_MAX = 20;
}

class LightManager
{
private:
	LightManager() = default;
	~LightManager() = default;
	
	//ライトの情報とカメラの位置
	struct LigDatas
	{
		DirLigData directionLight[DIRLIGHT_NUMBER_MAX];		
		PointLigData pointLight[POINTLIGHT_NUMBER_MAX];
		SpotLigData spotLight[SPOTLIGHT_NUMBER_MAX];
		Vector3 eyePos;
		int dirctionLightNum = 0;
		int pointLightNum = 0;											//ポイントライトの数
		int spotLightNum = 0;
	};
	LigDatas m_ligData;				//ライトのデータ
	int m_size = sizeof(m_ligData);	//ライトのデータのサイズ

	int m_dirctionLigCreateNum=0;//何番目に作ったか記録
	int m_pointLigCreateNum=0;
	int m_spotLightCreateNum=0;

public:

	static LightManager* m_instance;

	/**
	 * @brief ライトマネージャーのインスタンスを作成する
	*/
	static void CreateInstance()
	{
		if (!m_instance)
		{
			m_instance = new LightManager;
		}
	}

	/**
	 * @brief ライトマネージャーのインスタンスを削除する
	*/
	static void DeleteInstance()
	{
		delete m_instance;
		m_instance = nullptr;
	}

	/**
	 * @brief ライトマネージャーのインスタンスを取得する
	*/
	static LightManager* GetInstance() { return m_instance; }
	/**
	 * @brief ライトのデータの塊を取得する(定数バッファに渡す用)
	 * @return 全ライトのデータ
	*/

	LigDatas* GetLigDatas() { return &m_ligData; }

	/**
	 * @brief ライトのデータの塊のサイズを取得する(定数バッファに渡す用)
	 * @return 全ライトのデータのサイズ
	*/
	int GetLigDataSize() { return m_size; }

	/**
	 * @brief カメラのポジションを更新する
	 * @param カメラの番号
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