#include "stdafx.h"
#include "Tile.h"

namespace nsBalloon 
{
	Tile::~Tile()
	{

	}
	bool Tile::Start()
	{
		m_skinModelRender = NewGO<SkinModelRender>(0);
		m_skinModelRender->Init("Assets/modelData/TileStage/Tile01.tkm");
		m_skinModelRender->SetPosition(m_position);
		m_boxCollider.Create(btVector3(m_size.x, m_size.y, m_size.z));
		
		//剛体を初期化。	
		m_rbInfo.collider = &m_boxCollider;
		m_rbInfo.mass = 0.0f;
		m_rigidBody.Init(m_rbInfo);
		btTransform& trans = m_rigidBody.GetBody()->getWorldTransform();
		//剛体の位置を更新。
		trans.setOrigin(btVector3(m_position.x, m_position.y, m_position.z));

		return true;
	}
	void Tile::Update()
	{
		m_position.x += 0.8f;
		m_rbInfo.pos=m_position;
		m_rigidBody.ReInit(m_rbInfo);
		m_skinModelRender->SetPosition(m_position);
	}
}