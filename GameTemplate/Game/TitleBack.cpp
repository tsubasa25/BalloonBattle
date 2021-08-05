#include "stdafx.h"
#include "TitleBack.h"
#include "TitleScene.h"
namespace nsBalloon {
	TitleBack::~TitleBack()
	{
		DeleteGO(m_back_Sprite);
		DeleteGO(m_cloud1_Sprite);
		DeleteGO(m_cloud2_Sprite);
		DeleteGO(m_undercloud01_Sprite);
		DeleteGO(m_undercloud02_Sprite);
		DeleteGO(m_undercloud11_Sprite);
		DeleteGO(m_undercloud12_Sprite);
		DeleteGO(m_undercloud21_Sprite);
		DeleteGO(m_undercloud22_Sprite);
	}

	bool TitleBack::Start()
	{
		m_back_Sprite = NewGO<SpriteRender>(0);
		m_back_Sprite->Init("Assets/Image/back.dds", 1280, 720);

		m_cloud1_Sprite = NewGO<SpriteRender>(0);
		m_cloud1_Sprite->Init("Assets/Image/cloud.dds", 1280, 720);
		m_cloud2_Sprite = NewGO<SpriteRender>(0);
		m_cloud2_Sprite->Init("Assets/Image/cloud.dds", 1280, 720);
		m_cloud2_Sprite->SetPosition({ m_cloud2Pos });

		m_undercloud21_Sprite = NewGO<SpriteRender>(0);
		m_undercloud21_Sprite->Init("Assets/Image/under_cloud2.dds", 1282, 730);
		m_undercloud22_Sprite = NewGO<SpriteRender>(0);
		m_undercloud22_Sprite->Init("Assets/Image/under_cloud2.dds", 1282, 730);
		m_undercloud22_Sprite->SetPosition({ m_undercloud22Pos });

		m_undercloud11_Sprite = NewGO<SpriteRender>(0);
		m_undercloud11_Sprite->Init("Assets/Image/under_cloud1.dds", 1282, 740);
		m_undercloud12_Sprite = NewGO<SpriteRender>(0);
		m_undercloud12_Sprite->Init("Assets/Image/under_cloud1.dds", 1282, 740);
		m_undercloud12_Sprite->SetPosition({ m_undercloud12Pos });

		m_undercloud01_Sprite = NewGO<SpriteRender>(0);
		m_undercloud01_Sprite->Init("Assets/Image/under_cloud0.dds", 1282, 750);
		m_undercloud02_Sprite = NewGO<SpriteRender>(0);
		m_undercloud02_Sprite->Init("Assets/Image/under_cloud0.dds", 1282, 750);
		m_undercloud02_Sprite->SetPosition({ m_undercloud02Pos });


		return true;
	}

	void TitleBack::Update()
	{
		if (m_destroy == true)
		{
			DeleteGO(this);
		}
		if (m_cloud1Pos.x < -1280) {
			m_cloud1Pos.x = 1280;
		}
		if (m_cloud2Pos.x < -1280) {
			m_cloud2Pos.x = 1280;
		}
		if (m_undercloud01Pos.x > 1280) {
			m_undercloud01Pos.x = -1280;
		}
		if (m_undercloud02Pos.x > 1280) {
			m_undercloud02Pos.x = -1280;
		}
		if (m_undercloud11Pos.x > 1280) {
			m_undercloud11Pos.x = -1280;
		}
		if (m_undercloud12Pos.x > 1280) {
			m_undercloud12Pos.x = -1280;
		}
		if (m_undercloud21Pos.x > 1280) {
			m_undercloud21Pos.x = -1280;
		}
		if (m_undercloud22Pos.x > 1280) {
			m_undercloud22Pos.x = -1280;
		}


		m_cloud1Pos.x -= m_BM_MoveSpeed;
		m_cloud2Pos.x -= m_BM_MoveSpeed;
		m_undercloud21Pos.x += m_BM_MoveSpeed;
		m_undercloud22Pos.x += m_BM_MoveSpeed;
		m_undercloud11Pos.x += m_BM_MoveSpeed * 2;
		m_undercloud12Pos.x += m_BM_MoveSpeed * 2;
		m_undercloud01Pos.x += m_BM_MoveSpeed * 3;
		m_undercloud02Pos.x += m_BM_MoveSpeed * 3;

		m_cloud1_Sprite->SetPosition({ m_cloud1Pos });
		m_cloud2_Sprite->SetPosition({ m_cloud2Pos });

		m_undercloud21_Sprite->SetPosition({ m_undercloud21Pos });
		m_undercloud22_Sprite->SetPosition({ m_undercloud22Pos });
		m_undercloud11_Sprite->SetPosition({ m_undercloud11Pos });
		m_undercloud12_Sprite->SetPosition({ m_undercloud12Pos });
		m_undercloud01_Sprite->SetPosition({ m_undercloud01Pos });
		m_undercloud02_Sprite->SetPosition({ m_undercloud02Pos });

	}
}