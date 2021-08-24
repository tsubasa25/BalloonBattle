#pragma once
namespace nsBalloon {
	namespace nsTSConstant {
		const int METEORCRASH_INTERVAL = 300;
		const int METEORCRASH_SE_INTERVAL = METEORCRASH_INTERVAL-50;
		const int DANGERLIGHT_INTERVAL = METEORCRASH_INTERVAL - 75;
		const int TILE_NUM = 25;
		const float SOUND_METEOR_SE_VOLUME = 1.f;
		const float DANGERLIGHT_POS_Y = 100.f;		
		const float DANGERLIGHT_RANGE = 300.f;
		const Vector3 DANGERLIGHT_SCALE = { 0.5f,0.5f,0.5f };
		const Vector3 COLOR_RED = { 255.f,0.f,0.f };
		const float SOUND_DANGER_SE_VOLUME = 0.3f;
	}
	
	class TileStage :public IGameObject
	{
	public:
		bool Start()override;
		void Update()override;
		~TileStage();
		/// <summary>
		/// 隕石が落ちる
		/// </summary>
		void MeteorCrash();

		void DangerFlashing();
	private:
		Level m_level;
		Vector3 m_tilePos[nsTSConstant::TILE_NUM];
		int m_tileNum = 0;
		int m_meteorCrashTime = 0;//隕石が落ちてくる間隔	
		SkinModelRender* m_skinModelRender = nullptr;
		PhysicsStaticObject m_physicsStaticObject;				//CharaConとの当たり判定に使用する静的物理オブジェクト		
		Vector3 m_ligPos = Vector3::Zero;
		Effect m_dangerEff;
		SoundSource* m_ssMeteor = nullptr;

		float m_meteorPosX=0.f;
		float m_meteorPosZ=0.f;
		int m_tileCrashNum=0;

		int m_flashingLoopCount = 0;
		bool m_isMeteorOn = false;
	};
}