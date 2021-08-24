#include "stdafx.h"
#include "Thunder.h"
#include "Player.h"
namespace nsBalloon {
	Thunder::~Thunder()
	{
		
	}
	bool Thunder::Start()
	{		
		m_thunderEff.Init(u"Assets/effect/Thunder.efk");
		m_thunderEff.Play();
		m_thunderEff.SetPosition(m_position);
		m_thunderEff.Update();
		return true;
	}
	void Thunder::Update()
	{
		m_loopCount++;			
		if (m_loopCount > nsTConstant::DELAY_COUNT)
		{
			QueryGOs<Player>("player", [this](Player* player)->bool {
				//プレイヤーと針の位置の距離をとる
				Vector3 diff = player->GetPosition() - m_position;
				if (diff.Length() < 150.f)
				{
					player->BreakBalloon();
					player->PlayerDeath();
					SoundSource* ss = NewGO<SoundSource>(0);
					ss->Init(L"Assets/sound/風船の割れる音.wav");
					ss->Play(false);
					DeleteGO(this);
				}
				return true;
				});
		}
		if (m_thunderEff.IsPlay() == false)
		{
			DeleteGO(this);
		}
	}
	
}