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

	struct LigCameraDatas
	{
		Matrix lightCameraProjectionMatrix; //ライトビュープロジェクション行列
		Vector3 lightCameraPosition;//ライトカメラの位置
		float pad;
		Vector3 lightCameraDirection;//ライトカメラの向き
	};
	
	LigCameraDatas m_ligCameraData;
	int m_ligCameraDataSize = sizeof(m_ligCameraData);

	Camera m_lightCamera;//シャドウマップ用のライトの位置のカメラ。とりあえずテスト。
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

	//ライトの数をおしえる
	int GetDirectionLigNum() { return m_ligData.dirctionLightNum; }
	int GetPointLigNum() { return m_ligData.pointLightNum; }
	int GetSpotLigNum() { return m_ligData.spotLightNum; }

	//ライトの数を設定する
	void AddDirectionLigNum(int num) { m_ligData.dirctionLightNum = num + 1; }

	void AddPointLig(PointLigData* pointLigData) {
		//ライトの数が最初に決めた数以上ならthrowする(いっぱい作るとふつうに起こる)
		if (m_ligData.pointLightNum >= POINTLIGHT_NUMBER_MAX)
		{
			MessageBoxA(nullptr, "ポイントライトの数が最大数を超えています。\n", "エラー", MB_OK);
		}
		m_ligData.pointLight[GetPointLigNum()] = *pointLigData;//データを格納する
		pointLigData->pointLigNum = float(GetPointLigNum());//何番目に作られたか
		m_ligData.pointLightNum= float(GetPointLigNum()) +1.0f;//ライトの総数を一つ増やす
	}

	void AddSpotLigNum(int num) { m_ligData.spotLightNum=num+1; }

	void UpdateDirctionLight(int num) { m_ligData.dirctionLightNum = num; }

	void UpdatePointLight(int pointLigNum,PointLigData* pointLigData)
	{
		m_ligData.pointLight[pointLigNum] = *pointLigData;//
	}

	void UpdateSpotLight(int num) { m_ligData.spotLightNum = num; }

	void RemovePointLight(int num)
	{
		for (int i = num+1; i < GetPointLigNum()-1; i++) {
			m_ligData.pointLight[i] = m_ligData.pointLight[i + 1];//データをずらす
			m_ligData.pointLight[i].pointLigNum--;//自分が作られた番号もずらす
		}
		PointLightMinus();//ライトの数を減らす
	}
	/**
	 * @brief ポイントライトの数のカウントをマイナスする
	*/
	void PointLightMinus()
	{
		m_ligData.pointLightNum--;

		//ライトの数が0以下になる時はおかしくなっているのでthrowする(起こり得ないと信じたい)
		if (m_ligData.pointLightNum < 0)
		{
			MessageBoxA(nullptr, "ポイントライトの数がマイナスになっています。\n", "エラー", MB_OK);
		}
	}
	DirLigData* GetDirLigData() { return &m_ligData.directionLight[GetDirectionLigNum()]; }
	PointLigData* GetPointLigData() { return &m_ligData.pointLight[GetPointLigNum()]; }
	SpotLigData* GetSpotLigData() { return &m_ligData.spotLight[GetSpotLigNum()]; }
	
	////////////////////////////////////////////////////////////////////
	//影用
	/**
	 * @brief 影の描画に使用するライトカメラのデータの塊を取得する(定数バッファに渡す用)
	 * @return ライトカメラのデータ
	*/
	LigCameraDatas* GetLigCameraDatas() { return &m_ligCameraData; }

	/**
	 * @brief 影の描画に使用するライトカメラのデータの塊のサイズを取得する(定数バッファに渡す用)
	 * @return ライトカメラのデータのサイズ
	*/
	int GetLigCameraDataSize() { return m_ligCameraDataSize; }

	/**
	 * @brief 影の描画に使用するライトカメラを取得
	 * @return ライトカメラ
	*/
	Camera* GetLightCamera()
	{
		return &m_lightCamera;
	}

	/**
	 * @brief 影の描画に使用するライトカメラの座標を指定する
	 * @param pos ライトカメラの座標
	*/
	void SetLightCameraPosition(const Vector3& pos)
	{
		m_lightCamera.SetPosition(pos);
		m_lightCamera.Update();
		m_ligCameraData.lightCameraPosition = pos;
		m_ligCameraData.lightCameraProjectionMatrix = m_lightCamera.GetViewProjectionMatrix();

		m_ligCameraData.lightCameraDirection = m_lightCamera.GetTarget() - m_lightCamera.GetPosition();
		m_ligCameraData.lightCameraDirection.Normalize();
	}

	/**
	 * @brief 影の描画に使用するライトカメラのターゲットの座標を指定する
	 * @param targetPos ライトカメラのターゲットの座標
	*/
	void SetLightCameraTarget(const Vector3& targetPos)
	{
		m_lightCamera.SetTarget(targetPos);
		m_lightCamera.Update();
		m_ligCameraData.lightCameraProjectionMatrix = m_lightCamera.GetViewProjectionMatrix();

		m_ligCameraData.lightCameraDirection = m_lightCamera.GetTarget() - m_lightCamera.GetPosition();
		m_ligCameraData.lightCameraDirection.Normalize();
	}

	/**
	 * @brief 影の描画に使用するライトカメラの上方向を指定する
	 * @param up カメラの上方向のベクトル
	*/
	void SetLightCameraUp(const Vector3& up)
	{
		m_lightCamera.SetUp(up);
		m_lightCamera.Update();
		m_ligCameraData.lightCameraProjectionMatrix = m_lightCamera.GetViewProjectionMatrix();
	}

	/**
	 * @brief 影の描画に使用するライトカメラの射影行列の更新方法を設定する
	 * @param func 射影行列の更新方法
	*/
	void SetLightCameraUpdateProjMatrixFunc(Camera::EnUpdateProjMatrixFunc func)
	{
		m_lightCamera.SetUpdateProjMatrixFunc(func);
		m_lightCamera.Update();
		m_ligCameraData.lightCameraProjectionMatrix = m_lightCamera.GetViewProjectionMatrix();
	}

	/**
	 * @brief 影の描画に使用するライトカメラの横幅を指定する(平行投影限定)
	 * @param width ライトカメラの横幅
	*/
	void SetLightCameraWidth(const float& width)
	{
		m_lightCamera.SetWidth(width);
		m_lightCamera.Update();
		m_ligCameraData.lightCameraProjectionMatrix = m_lightCamera.GetViewProjectionMatrix();
	}

	/**
	 * @brief 影の描画に使用するライトカメラの高さを指定する(平行投影限定)
	 * @param height ライトカメラの高さ
	*/
	void SetLightCameraHeight(const float& height)
	{
		m_lightCamera.SetHeight(height);
		m_lightCamera.Update();
		m_ligCameraData.lightCameraProjectionMatrix = m_lightCamera.GetViewProjectionMatrix();
	}
};