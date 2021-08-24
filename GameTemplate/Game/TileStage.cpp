#include "stdafx.h"
#include "TileStage.h"
#include "Tile.h"
#include "Meteor.h"
#include "Thunder.h"
namespace nsBalloon {
	TileStage::~TileStage()
	{
	}
	bool TileStage::Start()
	{
		m_skinModelRender = NewGO<SkinModelRender>(0);
		m_skinModelRender->Init("Assets/modelData/TileStage/Wall.tkm");
		m_physicsStaticObject.CreateFromModel(m_skinModelRender->GetModel(), m_skinModelRender->GetModel().GetWorldMatrix());

		m_level.Init("Assets/modelData/TileStage/level01.tkl", [&](LevelObjectData& objData)
		{				
				if (strcmp(objData.name, "Tile0") == 0)
				{
					Tile* tile = NewGO<Tile>(0, "tile");
					tile->SetPosition(objData.position);
					m_tilePos[m_tileNum] = objData.position;
					m_tileNum++;
					return true;
				}			
				return false;
		});
		
		m_dangerEff.Init(u"Assets/effect/DangerLight.efk");
		m_dangerEff.SetScale(nsTSConstant::DANGERLIGHT_SCALE);
		
		return true;		
	}
	void TileStage::Update()
	{
		
		MeteorCrash();
		
	}
	void TileStage::MeteorCrash()
	{
		m_meteorCrashTime++;
		
		if (m_meteorCrashTime == nsTSConstant::METEORCRASH_SE_INTERVAL)
		{				
			m_tileCrashNum = rand() % nsTSConstant::TILE_NUM;
			m_ligPos = m_tilePos[m_tileCrashNum];//機器察知ライト用
			SoundSource* ssAlert = NewGO<SoundSource>(0);
			ssAlert->Init(L"Assets/sound/Alert.wav");
			ssAlert->SetVolume(nsTSConstant::SOUND_DANGER_SE_VOLUME);
			ssAlert->Play(false);
			if (rand() % 2 == 0)
			{
				m_isMeteorOn = true;
				m_ssMeteor = NewGO<SoundSource>(0);
				m_ssMeteor->Init(L"Assets/sound/MeteorLanding.wav");
				m_ssMeteor->SetVolume(nsTSConstant::SOUND_METEOR_SE_VOLUME);
				m_ssMeteor->Play(false);
			}
			else
			{
				m_isMeteorOn = false;
			}
		}
		if (m_meteorCrashTime >= nsTSConstant::METEORCRASH_SE_INTERVAL)
		{			
			DangerFlashing();
		}
		if (m_meteorCrashTime > nsTSConstant::METEORCRASH_INTERVAL)
		{
			m_meteorCrashTime = 0;
			if (m_isMeteorOn == true)
			{
				m_meteorPosX = rand() % 4000;
				m_meteorPosZ = rand() % 4000;
				Meteor* meteor = NewGO<Meteor>(0, "meteor");
				meteor->SetPosition({ (m_meteorPosX - 2000.f),2000,(m_meteorPosZ - 2000.f) });
				meteor->SetTilePosition(m_tilePos[m_tileCrashNum]);
			}
			else
			{
				Thunder* thunder = NewGO<Thunder>(0, "thunder");
				thunder->SetPosition(m_ligPos);
				
			}
		}
	}
	void TileStage::DangerFlashing()
	{
		m_flashingLoopCount++;
		if (m_flashingLoopCount == 20)
		{
			m_flashingLoopCount = 0;
			m_dangerEff.Play();			
			m_dangerEff.SetPosition(m_ligPos);
			m_dangerEff.Update();			
		}
	}
}