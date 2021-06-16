#pragma once

class DirectionLight;
class PointLight;
class SpotLight;

class SkinModelRender:public IGameObject
{
public:
	SkinModelRender() :m_position(Vector3::Zero), m_qRot(g_quatIdentity), m_scale(Vector3::One) {}
	~SkinModelRender();
	void Update();
	/**
	 * @brief モデルの情報を更新する
	*/
	void UpdateModel();

	
	void Render(RenderContext& rc)override;
	/**
		 * @brief モデルの描画
		 * @param rc レンダーコンテキスト
		 * @param camera 描画するカメラ
		*/
	
	/**
		 * @brief モデルの初期化関数　アニメーションつき
		 * @param modelPath モデルファイルのパス(.tkm)
		 * @param skeletonPath スケルトンファイルのパス(.tks)
		 * @param animClips アニメーションクリップの配列
		 * @param animClipNum アニメーションクリップの数
		*/
	void Init(const char* modelPath, const char* skeletonPath, AnimationClip* animClips, int animClipNum);

	/**
		 * @brief モデルの初期化関数
		 * @param modelPath モデルファイルのパス(.tkm)
		 * @param skeletonPath スケルトンファイルのパス(.tks)
		*/
	void Init(const char* modelPath, const char* skeletonPath);
	/**
		 * @brief モデルの初期化関数　モデルパスだけ版
		 * @param modelPath モデルファイルのパス(.tkm)
		*/
	void Init(const char* modelPath);
	
	/**
		 * @brief モデルの座標を設定する
		 * @param pos 座標
		*/
	void SetPosition(Vector3 pos);
	void SetPositionX(float posX);
	void SetPositionZ(float posZ);
	/**
		 * @brief モデルの回転を設定する
		 * @param qRot 回転
		*/
	void SetRotation(Quaternion qRot);
	/**
		 * @brief モデルの拡大率を設定する
		 * @param scale 拡大率
		*/
	void SetScale(Vector3 scale);
	
	/**
		 * @brief モデルの座標を取得
		 * @return 座標
		*/
	Vector3 GetPosition()
	{
		return m_position;
	}
	float GetPositionX()
	{
		return m_position.x;
	}
	float GetPositionY()
	{
		return m_position.y;
	}
	float GetPositionZ()
	{
		return m_position.z;
	}
	/**
		 * @brief モデルの回転を取得
		 * @return 回転
		*/
	Quaternion GetRotation()
	{
		return m_qRot;
	}

	/**
	 * @brief モデルの拡大率を取得
	 * @return 拡大率
	*/
	Vector3 GetScale()
	{
		return m_scale;
	}
	/**
		 * @brief モデルを取得
		 * @param model ビューポート番号(カメラ番号)
		 * @return 番号から取得したモデルへの参照
		*/
	Model& GetModel()
	{
		return m_model;
	}
private:
	
	Skeleton m_skeleton; //スケルトン
	Model m_model; //モデル
	Vector3 m_position; //座標
	Quaternion m_qRot; //回転
	Vector3 m_scale; //拡大率

};

