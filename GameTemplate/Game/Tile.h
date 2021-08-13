#pragma once

namespace nsBalloon{
	namespace nsTConstant {
		const Vector3 INI_TILE_SIZE = { 220,30,220 };
}
	class Tile :public IGameObject
	{
	public:
		bool Start()override;
		void Update()override;
		~Tile();

		void SetPosition(Vector3 pos) { m_position = pos; }
		Vector3& GetPosition() { return m_position; }
	private:
		SkinModelRender* m_skinModelRender = nullptr;
		BoxCollider m_boxCollider;//当たり判定の形
		RigidBody m_rigidBody;//ボックスコライダーを動かすためのデータ
		RigidBodyInitData m_rbInfo;
		
		Vector3 m_position = Vector3::Zero;
		Vector3 m_size = nsTConstant::INI_TILE_SIZE;
		Quaternion m_rot = Quaternion::Identity;
	};
}