#pragma once
#include<vector>
namespace nsBalloon {
	class BalloonAir;
	class BackGround;
	class UIDisplay;
	class ResultScene;
	class GameScene;


	namespace nsPlConstant
	{
		const int MASS_DIVISOR = 20;//風船の大きさから質量を出すときの割る値
		const float REBOUND_POWER = 1.5;//敵と衝突したとき、勢いにかける値
		const int INI_AIR_VOLUME = 150;//風船の空気の量の初期値
		const float BALLOON_SIZE_BASE = 100;	//風船の大きさの基本値
		const Vector3 POINTLIGHT_COLOR = { 10,10,10 };//ポイントライトの色
		const int POINTLIGHT_RANGE = 200;//ポイントライトの影響範囲
		const int DESELE_VOLUME = 50;//減速させる大きさを調整する値
		const float GRAVITY_SPEED = 0.7f;//落下スピード
		const float GRAVITY_INDEX = 2.0f;//落下スピードにかける指数
		const float PAI = 3.14159f;//円周率
		const Vector3 OVER_STAGE_LINE = { 4000.0f, -2000.0f, 4000.0f };	//ステージから遠ざかりすぎた時に死亡する距離。
		const float SOUND_BALLOON_SE_VOLUME = 0.4f;
		const int RESPAWN_INTERVAL = 50;
	}
	class Player :public IGameObject
	{

	public:
		~Player();
		bool Start();
		void Update();

		void SetCanMove(bool can) { m_canMove = can; };
		bool GetCanMove() { return m_canMove; };
		/// <summary>
		/// プレイヤー番号を設定する
		/// </summary>
		/// <param name="num">プレイヤー番号</param>
		void SetPlayerNum(int num) { m_playerNum = num; }
		/// <summary>
		/// プレイヤー番号を取得する
		/// </summary>
		/// <returns>プレイヤー番号</returns>
		const int& GetPlayerNum() const { return m_playerNum; }

		void SetPlayerStock(int num) { m_stock = num; }
		int GetPlayerStock() { return m_stock; }//プレイヤーのストック数を入手する

		void SetPlayerCount(int num) { m_playerCount = num; }//プレイヤー人数を設定する

		void SetEnemyData(Player* enemy) { m_enemy.push_back(enemy); }//敵情報を設定する

		void SetIniPosition(Vector3 pos) { m_position = pos; m_iniPos = pos; }//初期位置を設定
		void SetPosition(Vector3 pos) { m_skinModelRender->SetPosition(pos); m_position = pos; }
		void ReturnIniPosition() { SetPosition(m_iniPos); };

		Vector3 GetPosition() { return m_position; }

		void SetScale(Vector3 scale) { m_skinModelRender->SetScale(scale); }//大きさ
		Vector3 GetScale() { return m_skinModelRender->GetScale(); }

		Vector3 Decele(Vector3 decele);//減速処理

		void AddMoveSpeed(Vector3 dir) { m_moveSpeed += dir; }//コントローラー入力の値を加算合計する
		void SetMoveSpeed(Vector3 dir) { m_moveSpeed = dir; }//再設定する
		Vector3 GetMoveSpeed() { return m_moveSpeed; }

		void Move();//移動関数

		void HitWall();//壁にあたったとき

		void HitPlayer();//プレイヤーに合ったとき

		Vector3 ReboundSpeed();//モデルの法線から反射する方向を求めて移動方向を決定する

		float GetAirVolume() { return m_myAirVolume; };
		void SetAirVolume(float air) { m_myAirVolume = air; };	//風船の空気の量を設定

		int GetKillPoint() { return m_killPoint; }
		void AddKillPoint() { m_killPoint++; }

		void Tilt();	//風船の傾きを決める。

		void PlayerDeath();	//キャラクターが死亡したときの処理
		void BreakBalloon();	//風船破裂の処理。引数の位置で破裂エフェクトを表示
		void PlayEffHit();	//プレイヤーの衝突時のエフェクト再生

		void Respawn();
		void WaitRespawn() { m_respawnCount += nsPlConstant::RESPAWN_INTERVAL; };

		Vector4 GetPlColor() { return m_plColor; };

		//デバッグ用
		void Debug(int pNum);

		void SetArrowScele(Vector3 size) { m_skinModelRenderArrow->SetScale(size); };
	private:

		bool m_canMove = false;

		Vector3 m_scale = { Vector3::Zero };
		int m_playerNum = 0;//プレイヤー番号
		int m_stock = 3;//ストック
		int m_playerCount = 0;

		Vector3 m_position = { Vector3::Zero };
		Vector3 m_iniPos = { Vector3::Zero };
		Vector3 m_resPos = { Vector3::Zero };	//リスポーン位置
		Vector3 m_decele = { Vector3::Zero };
		Vector3 m_moveSpeed = { Vector3::Zero };

		Vector3 m_lightPos = { Vector3::Zero };

		CharacterController m_charaCon;//プレイヤーのキャラコン

		SkinModelRender* m_skinModelRender = nullptr;

		BalloonAir* m_myAir = nullptr;

		float m_myAirVolume = nsPlConstant::INI_AIR_VOLUME;
		/// <summary>
		/// 
		/// </summary>
		Quaternion m_playerRot = { 0.0f,0.0f,0.0f,0.0f };
		std::vector<Player*> m_enemy;
		std::vector<Player*>::iterator it;
		BackGround* m_backGround = nullptr;
		UIDisplay* m_UIDisplay = nullptr;
		GameScene* m_gameScene = nullptr;
		Effect m_breakEff;

		ResultScene* m_resultScene = nullptr;

		Effect m_hitEff;

		bool m_respawnFlag = false;
		int m_respawnCount = 0;
		Vector4 m_plColor = { 0.0f,0.0f,0.0f,1.0f };

		int m_hitLastNum = 99;//最後にあたった敵の番号
		int m_killPoint = 0;

		//デバッグ用

		int m_oldStock = m_stock;
		bool m_isArrowOn = true;//矢印を表示するか
		bool m_isAIOn = false;//敵が自分めがけて突進してくる
		SkinModelRender* m_skinModelRenderArrow = nullptr;

		Quaternion m_rot = Quaternion::Identity;
		Vector3 m_arrowSize = Vector3::One;
		Vector3 m_oldPos = Vector3::Zero;
	};
}

