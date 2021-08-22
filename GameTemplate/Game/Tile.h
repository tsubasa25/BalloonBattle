#pragma once

namespace nsBalloon{
	namespace nsTConstant {
		const Vector3 INI_TILE_SIZE = { 200,10,200 };
		const Vector3 HIT_EFFECT_SCALE = { 10,10,10 };
		const float SOUND_METEOR_SE_VOLUME = 1.f;
}
	class Tile :public IGameObject
	{
	public:
		bool Start()override;
		void Update()override;
		~Tile();

		void SetPosition(Vector3 pos) { m_position = pos; }
		Vector3& GetPosition() { return m_position; }

		void SetTileNum(int num) { m_tileNum = num; }
		int GetTileNum() { return m_tileNum; }

		void HitMeteor();//隕石が当たる
	private:
		SkinModelRender* m_skinModelRender = nullptr;
		BoxCollider m_boxCollider;//当たり判定の形
		RigidBody m_rigidBody;//ボックスコライダーを動かすためのデータ
		RigidBodyInitData m_rbInfo;
		
		Vector3 m_position = Vector3::Zero;
		Vector3 m_size = nsTConstant::INI_TILE_SIZE;
		Quaternion m_rot = Quaternion::Identity;
		SoundSource* m_ssMeteor = nullptr;
		int m_tileNum = 0;
	};
}