#pragma once
namespace nsBalloon {
	class DirectionLight;
	class PointLight;
	class SpotLight;

	class SkinModelRender :public IGameObject
	{
	public:
		//モデルの状態
		enum EModel {
			eModel,	//画面に描画されるモデル		
			eModel_Shadow,	//影を描画する用モデル		
			eModel_Num,		//モデルの状態の数
		};
		SkinModelRender() :m_position(Vector3::Zero), m_qRot(g_quatIdentity), m_scale(Vector3::One) {}
		~SkinModelRender();
		void Update();
		/**
		 * @brief モデルの情報を更新する
		*/
		void UpdateModel();


		void Render(RenderContext& rc, Camera* camera)override;
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
			 * @brief アニメーションの再生
			 * @param animationNo アニメーション番号
			 * @param interpolateTime アニメーションの補完時間
			*/
		void PlayAnimation(int animationNo, float interpolateTime = 0.0f)
		{
			m_animation.Play(animationNo, interpolateTime);
			m_animation.Progress(m_animationSpeed / 60.0f);
			UpdateModel();
		}
		/**
			 * @brief アニメーションを再生しているか?
			 * @return 再生している:true 再生していない:false
			*/
		bool IsPlayingAnimation() const
		{
			return m_animation.IsPlaying();
		}
		/**
			 * @brief アニメーションの再生速度を設定する
			 * @param animationSpeed 再生速度
			*/
		void SetAnimationSpeed(float animationSpeed)
		{
			m_animationSpeed = animationSpeed;
		}
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
			 * @brief モデルのワールド行列を直接セットする
			 * @param world ワールド行列
			*/
		void SetMatrix(Matrix world)
		{
			for (auto& model : m_model) {
				model.UpdateWorldMatrix(world);
				m_skeleton.Update(world);
			}
		}
		/**
				 * @brief モデルが影を作るかどうかを設定する
				 * @param isShadowCaster 作る:true 作らない:false
				*/
		void SetShadowCasterFlag(bool isShadowCaster)
		{
			m_isShadowCaster = isShadowCaster;
		}
		/**
			 * @brief モデルと線分が交差している?
			 * @param start 線分の始点
			 * @param end 線分の終点
			 * @param crossPoint 線分の交差点(戻り値、参照受け取り)
			 * @return 交差している:true 交差していない:false
			*/
		bool isLineHitModel(const Vector3& start, const Vector3& end, Vector3& crossPoint);

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
		Model& GetModel(EModel model = eModel)
		{
			return m_model[model];
		}
		/**
			 * @brief ボーンの名前からそのボーンのワールド行列を取得する
			 * @param boneName ボーンの名前
			 * @return ボーンのワールド行列
			*/
		Matrix GetWorldMatrixFromBoneName(const wchar_t* boneName);

		/**
			 * @brief 事前にモデルをロードしておく
			 * @param tkmFilePath ロードしたいモデルのファイルパス
			*/
		static void PreLoadModel(const char* tkmFilePath);

	private:

		Skeleton m_skeleton; //スケルトン
		Model m_model[eModel_Num]; //モデル
		Vector3 m_position; //座標
		Quaternion m_qRot; //回転
		Vector3 m_scale; //拡大率
		AnimationClip* m_animationClips = nullptr;	//アニメーションクリップ
		int m_animationClipNum = 0;					//アニメーションクリップの数
		Animation m_animation;						//アニメーション。
		bool m_isShadowCaster = false;				//このモデルは影を作るか?
		float m_animation_speed = 1.0;				//アニメーション速度
		float m_animationSpeed = 1.0f;
	};
}