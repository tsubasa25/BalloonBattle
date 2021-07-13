#pragma once
class Sky:public IGameObject
{
public: 
	
/**
		 * @brief モデルの初期化関数　アニメーションつき
		 * @param modelPath モデルファイルのパス(.tkm)
		 * @param skeletonPath スケルトンファイルのパス(.tks)
		 * @param animClips アニメーションクリップの配列
		 * @param animClipNum アニメーションクリップの数
		*/
	void Init();
	void Render(RenderContext& rc, Camera* camera)override;
	void Update()override;
private:
	Model m_model; //モデル
	Vector3 m_scale = { 8000.0f, 8000.0f, 8000.0f };		//空の拡大率。
	Quaternion m_qRot;
	Vector3 m_position = Vector3::Zero;					//座標。
	Texture m_skyTexture;
	bool m_isDirty = false;									//ダーティフラグ。

};

