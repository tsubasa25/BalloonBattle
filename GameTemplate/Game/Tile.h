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
		BoxCollider m_boxCollider;//�����蔻��̌`
		RigidBody m_rigidBody;//�{�b�N�X�R���C�_�[�𓮂������߂̃f�[�^
		RigidBodyInitData m_rbInfo;
		
		Vector3 m_position = Vector3::Zero;
		Vector3 m_size = nsTConstant::INI_TILE_SIZE;
		Quaternion m_rot = Quaternion::Identity;
	};
}