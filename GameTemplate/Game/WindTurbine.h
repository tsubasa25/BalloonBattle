#pragma once
namespace nsBalloon {
	class GameScene;
	namespace nsWTConstant
	{
		const int WT_NOT_MOVE_INTERVAL = 400;	//風車が動いていない時間
		const int WT_MOVE_INTERVAL = 250;		//風車が動いている時間
	}
	class WindTurbine :public IGameObject
	{
	public:
		~WindTurbine();
		bool Start();
		void Update();
		void BladesSpin();

		void SetPosition(Vector3 pos) { m_position = pos; }
		void SetWTBledesPos(Vector3 pos) { m_WTBladesPos = pos; }
	private:
		FontRender* m_font;

		Quaternion m_rot = { 0.0f,0.0f,0.0f, 0.0f };
		Quaternion m_rotY = { 0.0f,1.0f,0.0f, 0.0f };
		Quaternion m_rotZ = { 0.0f,0.0f,0.0f, 0.0f };
		SkinModelRender* m_WTBaseModelRender = nullptr;//支柱
		SkinModelRender* m_WTBladesModelRender = nullptr;//ブレード
		PhysicsStaticObject m_physicsStaticObject;				//CharaConとの当たり判定に使用する静的物理オブジェクト

		Vector3 m_position = { Vector3::Zero };//位置


		float m_angle = 0.0f;//Y軸の回転角度
		Vector3 m_frontY = { 0.0f,0.0f, -1.0f };//前を向いている方向
		Vector3 m_frontZ = { 0.0f,0.0f, 0.0f };
		//Vector3 m_front = { 0.0f,0.0f, 0.0f };
		float a = 0.0f;
		float b = 0.0f;
		Vector3 m_diff;//プレイヤーとの距離

		Vector3 m_WTBladesPos = { 0.0f, 0.0f, 0.0f };//ブレードの位置
		int WTMoveTimer = 0;//ループカウント
		bool WTMoveFlag = false;//風車が動くかどうか
		Quaternion m_bladesRot = { 0.0f,0.0f,1.0f, 0.0f };//X軸の回転とY軸の回転
		float m_bladesSpinPower = 0.01f;//回転スピード
		float m_WTBladesAngle = 0.0f;//
		Effect eff;

		GameScene* m_gameScene = nullptr;
	};
}