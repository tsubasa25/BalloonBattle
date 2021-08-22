#include "stdafx.h"
#include "Tile.h"
#include "Meteor.h"

namespace nsBalloon 
{
	Tile::~Tile()
	{
		DeleteGO(m_skinModelRender);
	}
	bool Tile::Start()
	{
		m_skinModelRender = NewGO<SkinModelRender>(0);
		m_skinModelRender->SetShadowCasterFlag(false);
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
		m_rbInfo.pos=m_position;
		m_rigidBody.ReInit(m_rbInfo);
		m_skinModelRender->SetPosition(m_position);
		HitMeteor();//隕石が当たればタイルが消える
	}
	void Tile::HitMeteor()
	{
		QueryGOs<Meteor>("meteor", [this](Meteor* meteor)->bool {
			Vector3 diff = meteor->GetPosition() - m_position;
			if (diff.Length()<1.f) {
				Effect hitEff;
				hitEff.Init(u"Assets/effect/HitEff.efk");
				hitEff.SetScale(nsTConstant::HIT_EFFECT_SCALE);
				hitEff.Play();
				m_ssMeteor = NewGO<SoundSource>(0);
				m_ssMeteor->Init(L"Assets/sound/MeteorHit.wav");
				m_ssMeteor->SetVolume(nsTConstant::SOUND_METEOR_SE_VOLUME);
				m_ssMeteor->Play(false);
				DeleteGO(this);
			}
			return true;
			});
	}
}