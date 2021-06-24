#include "stdafx.h"
#include "WindTurbine.h"
#include "Player.h"
WindTurbine::~WindTurbine()
{

}

bool WindTurbine::Start()
{
	m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->Init("Assets/modelData/WindTurbine.tkm");
	
	SetPosition(m_position);


	return true;
}

void WindTurbine::Update()
{
	m_front={ -1.0f,0.0f, 0.0f };//基準ベクトル（最初に向いている向き::これ必要）
	a += 0.01f;//回すスピード
	
	m_front.Normalize();//正規化
	m_rot.SetRotation(Vector3::AxisY, a);//aの分だけ回す
	m_rot.Apply(m_front);//正面ベクトルの向きを変える
	
	//プレイヤーを探す
	QueryGOs<Player>("player", [this](Player* player)->bool {
		m_diff = player->GetPosition()- m_position;//プレイヤーと風車の位置の距離をとる
		
		if (m_diff.Length() <= 5000) {//5000以内にプレイヤーがいれば
			m_diff.Normalize();
			float n = m_front.Dot(m_diff);
			m_angle = acosf(n);
			if (m_diff.z < 0) {
				m_angle *= -1;
			}
			if (m_angle <= 0.3 && m_angle >= -0.3) {
				player->AddMoveSpeed(m_front/2);
			}
		}

		return true;
	});
	m_skinModelRender->SetRotation(m_rot);	
}