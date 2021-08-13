#include "stdafx.h"
#include "TileStage.h"
#include "Tile.h"
namespace nsBalloon {
	TileStage::~TileStage()
	{

	}
	bool TileStage::Start()
	{			
		m_level.Init("Assets/modelData/TileStage/level01.tkl", [&](LevelObjectData& objData)
		{
				if (strcmp(objData.name, "Tile0") == 0)
				{
					Tile* tile = NewGO<Tile>(0);
					tile->SetPosition(objData.position);
					return true;
				}
				return false;
		});		
		return true;
	}
	void TileStage::Update()
	{

	}
}