#include "stdafx.h"
#include "UIDisplay.h"
#include "GameScene.h"
#include "Player.h"
namespace nsBalloon {
	UIDisplay::~UIDisplay()
	{
		for (int i = 0; i < PLAYER_MAX_COUNT; i++)
		{
			if (m_playerUI_Sprite[i] != nullptr)
			{
				DeleteGO(m_playerUI_Sprite[i]);
			}
			if (m_playerstock_Sprite[i] != nullptr)
			{
				DeleteGO(m_playerstock_Sprite[i]);
			}
			if (m_playerstock_FontRender[i] != nullptr)
			{
				DeleteGO(m_playerstock_FontRender[i]);
			}
		}
	}
	bool UIDisplay::Start()
	{
		QueryGOs<Player>("player", [this](Player* player)->bool {
			for (int i = 0; i < PLAYER_MAX_COUNT; i++) {
				if (player->GetPlayerNum() == i) {
					m_playerUI_Sprite[i] = NewGO<SpriteRender>(0);
					m_playerstock_Sprite[i] = NewGO<SpriteRender>(0);
					m_minusPoint_Sprite[i] = NewGO<SpriteRender>(0);
					m_minusPoint_Sprite[i]->Init("Assets/Image/minus.dds", 100, 100);
					m_minusPoint_Sprite[i]->SetPosition(m_minusPointPos[i]);
					m_minusPoint_Sprite[i]->SetScale(Vector3::Zero);
					m_plusPoint_Sprite[i] = NewGO<SpriteRender>(0);
					m_plusPoint_Sprite[i]->Init("Assets/Image/plus.dds", 100, 100);
					m_plusPoint_Sprite[i]->SetPosition(m_plusPointPos[i]);
					m_plusPoint_Sprite[i]->SetScale(Vector3::Zero);

					m_playerstock_FontRender[i] = NewGO<FontRender>(0);

					switch (i)
					{
					case 0:
						m_playerUI_Sprite[i]->Init("Assets/Image/ballooooooon.red.dds", 252, 420);
						m_playerstock_Sprite[i]->Init("Assets/Image/balloon.red2.dds", nsUIDConstant::STOCK_UI_SIZE, nsUIDConstant::STOCK_UI_SIZE);
						break;
					case 1:
						m_playerUI_Sprite[i]->Init("Assets/Image/ballooooooon.blue.dds", 252, 420);
						m_playerstock_Sprite[i]->Init("Assets/Image/balloon.blue2.dds", nsUIDConstant::STOCK_UI_SIZE, nsUIDConstant::STOCK_UI_SIZE);
						break;
					case 2:
						m_playerUI_Sprite[i]->Init("Assets/Image/ballooooooon.green.dds", 252, 420);
						m_playerstock_Sprite[i]->Init("Assets/Image/balloon.green2.dds", nsUIDConstant::STOCK_UI_SIZE, nsUIDConstant::STOCK_UI_SIZE);
						break;
					case 3:
						m_playerUI_Sprite[i]->Init("Assets/Image/ballooooooon.yellow.dds", 252, 420);
						m_playerstock_Sprite[i]->Init("Assets/Image/balloon.yellow2.dds", nsUIDConstant::STOCK_UI_SIZE, nsUIDConstant::STOCK_UI_SIZE);
						break;
					case 4:
						m_playerUI_Sprite[i]->Init("Assets/Image/ballooooooon.orange.dds", 252, 420);
						m_playerstock_Sprite[i]->Init("Assets/Image/balloon.orange2.dds", nsUIDConstant::STOCK_UI_SIZE, nsUIDConstant::STOCK_UI_SIZE);
						break;
					case 5:
						m_playerUI_Sprite[i]->Init("Assets/Image/ballooooooon.pink.dds", 252, 420);
						m_playerstock_Sprite[i]->Init("Assets/Image/balloon.pink2.dds", nsUIDConstant::STOCK_UI_SIZE, nsUIDConstant::STOCK_UI_SIZE);
						break;
					case 6:
						m_playerUI_Sprite[i]->Init("Assets/Image/ballooooooon.gray.dds", 252, 420);
						m_playerstock_Sprite[i]->Init("Assets/Image/balloon.gray2.dds", nsUIDConstant::STOCK_UI_SIZE, nsUIDConstant::STOCK_UI_SIZE);
						break;
					case 7:
						m_playerUI_Sprite[i]->Init("Assets/Image/ballooooooon.purple.dds", 252, 420);
						m_playerstock_Sprite[i]->Init("Assets/Image/balloon.purple2.dds", nsUIDConstant::STOCK_UI_SIZE, nsUIDConstant::STOCK_UI_SIZE);
						break;
					default:
						break;
					}

					m_playerUI_Sprite[i]->SetScale(nsUIDConstant::PLAYER_UI_SIZE);
					m_playerUI_Sprite[i]->SetPosition(m_playerUI_Pos[i]);

					m_playerstock_Sprite[i]->SetScale(nsUIDConstant::PLAYER_STOCK_SIZE);
					m_playerstock_Sprite[i]->SetPosition(m_playerstock_Pos[i]);

					m_playerstock_FontRender[i]->SetColor(nsUIDConstant::STOCKNUM_COLOR);
					m_playerstock_FontRender[i]->SetPosition(nsUIDConstant::PL_STOCKNUM_POS[i]);
					m_playerstock_FontRender[i]->SetScale({ nsUIDConstant::STOCKNUM_SIZE });
					m_playerstock_FontRender[i]->SetText(L"x" + std::to_wstring(player->GetPlayerStock()));
					break;
				}
			}

			return true;
			});

		return true;
	}
	void UIDisplay::Update()
	{
		if (m_isDeath == true) {
			QueryGOs<Player>("player", [this](Player* player)->bool {
				for (int i = 0; i < PLAYER_MAX_COUNT; i++) {
					if (player->GetPlayerNum() == i) {
						for (int j = 1; j < 6; j++) {
							if (player->GetPlayerStock() == j) {
								m_playerstock_FontRender[i]->SetText(m_stocknum[j]);
								break;
							}
						}
						break;
					}
				}
				return true;
				});
			for (int i = 0; i < PLAYER_MAX_COUNT; i++) {
				if (m_PlDeath[i] == true) {
					m_playerstock_FontRender[i]->SetText(m_stocknum[0]);
				}
			}
			m_isDeath = false;
		}
		for (int i = 0; i < PLAYER_MAX_COUNT; i++) {
			MinusDisplay(i);
			if (m_PlDecStock[i] == true) {
				switch (i)
				{
				case 0:
					explosioncount[i] += 1;
					if (explosioncount[i] == changeframenum[0]) {
						m_playerstock_Sprite[i]->Init("Assets/Image/balloon.red4.dds", nsUIDConstant::STOCK_UI_SIZE, nsUIDConstant::STOCK_UI_SIZE);
						break;
					}
					if (explosioncount[i] == changeframenum[1]) {
						m_playerstock_Sprite[i]->Init("Assets/Image/balloon.red5.dds", nsUIDConstant::STOCK_UI_SIZE, nsUIDConstant::STOCK_UI_SIZE);
						break;
					}
					if (explosioncount[i] == changeframenum[2]) {
						m_playerstock_Sprite[i]->Init("Assets/Image/balloon.red6.dds", nsUIDConstant::STOCK_UI_SIZE, nsUIDConstant::STOCK_UI_SIZE);
						break;
					}
					if (explosioncount[i] == changeframenum[3]) {
						m_playerstock_Sprite[i]->Init("Assets/Image/balloon.red2.dds", nsUIDConstant::STOCK_UI_SIZE, nsUIDConstant::STOCK_UI_SIZE);
						explosioncount[i] = 0;
						m_PlDecStock[i] = false;
						break;
					}
					break;
				case 1:
					explosioncount[i] += 1;
					if (explosioncount[i] == changeframenum[0]) {
						m_playerstock_Sprite[i]->Init("Assets/Image/balloon.blue4.dds", nsUIDConstant::STOCK_UI_SIZE, nsUIDConstant::STOCK_UI_SIZE);
						break;
					}
					if (explosioncount[i] == changeframenum[1]) {
						m_playerstock_Sprite[i]->Init("Assets/Image/balloon.blue5.dds", nsUIDConstant::STOCK_UI_SIZE, nsUIDConstant::STOCK_UI_SIZE);
						break;
					}
					if (explosioncount[i] == changeframenum[2]) {
						m_playerstock_Sprite[i]->Init("Assets/Image/balloon.blue6.dds", nsUIDConstant::STOCK_UI_SIZE, nsUIDConstant::STOCK_UI_SIZE);
						break;
					}
					if (explosioncount[i] == changeframenum[3]) {
						m_playerstock_Sprite[i]->Init("Assets/Image/balloon.blue2.dds", nsUIDConstant::STOCK_UI_SIZE, nsUIDConstant::STOCK_UI_SIZE);
						explosioncount[i] = 0;
						m_PlDecStock[i] = false;
						break;
					}
					break;
				case 2:
					explosioncount[i] += 1;
					if (explosioncount[i] == changeframenum[0]) {
						m_playerstock_Sprite[i]->Init("Assets/Image/balloon.green4.dds", nsUIDConstant::STOCK_UI_SIZE, nsUIDConstant::STOCK_UI_SIZE);
						break;
					}
					if (explosioncount[i] == changeframenum[1]) {
						m_playerstock_Sprite[i]->Init("Assets/Image/balloon.green5.dds", nsUIDConstant::STOCK_UI_SIZE, nsUIDConstant::STOCK_UI_SIZE);
						break;
					}
					if (explosioncount[i] == changeframenum[2]) {
						m_playerstock_Sprite[i]->Init("Assets/Image/balloon.green6.dds", nsUIDConstant::STOCK_UI_SIZE, nsUIDConstant::STOCK_UI_SIZE);
						break;
					}
					if (explosioncount[i] == changeframenum[3]) {
						m_playerstock_Sprite[i]->Init("Assets/Image/balloon.green2.dds", nsUIDConstant::STOCK_UI_SIZE, nsUIDConstant::STOCK_UI_SIZE);
						explosioncount[i] = 0;
						m_PlDecStock[i] = false;
						break;
					}
					break;
				case 3:
					explosioncount[i] += 1;
					if (explosioncount[i] == changeframenum[0]) {
						m_playerstock_Sprite[i]->Init("Assets/Image/balloon.yellow4.dds", nsUIDConstant::STOCK_UI_SIZE, nsUIDConstant::STOCK_UI_SIZE);
						break;
					}
					if (explosioncount[i] == changeframenum[1]) {
						m_playerstock_Sprite[i]->Init("Assets/Image/balloon.yellow5.dds", nsUIDConstant::STOCK_UI_SIZE, nsUIDConstant::STOCK_UI_SIZE);
						break;
					}
					if (explosioncount[i] == changeframenum[2]) {
						m_playerstock_Sprite[i]->Init("Assets/Image/balloon.yellow6.dds", nsUIDConstant::STOCK_UI_SIZE, nsUIDConstant::STOCK_UI_SIZE);
						break;
					}
					if (explosioncount[i] == changeframenum[3]) {
						m_playerstock_Sprite[i]->Init("Assets/Image/balloon.yellow2.dds", nsUIDConstant::STOCK_UI_SIZE, nsUIDConstant::STOCK_UI_SIZE);
						explosioncount[i] = 0;
						m_PlDecStock[i] = false;
						break;
					}
					break;
				case 4:
					explosioncount[i] += 1;
					if (explosioncount[i] == changeframenum[0]) {
						m_playerstock_Sprite[i]->Init("Assets/Image/balloon.orange4.dds", nsUIDConstant::STOCK_UI_SIZE, nsUIDConstant::STOCK_UI_SIZE);
						break;
					}
					if (explosioncount[i] == changeframenum[1]) {
						m_playerstock_Sprite[i]->Init("Assets/Image/balloon.orange5.dds", nsUIDConstant::STOCK_UI_SIZE, nsUIDConstant::STOCK_UI_SIZE);
						break;
					}
					if (explosioncount[i] == changeframenum[2]) {
						m_playerstock_Sprite[i]->Init("Assets/Image/balloon.orange6.dds", nsUIDConstant::STOCK_UI_SIZE, nsUIDConstant::STOCK_UI_SIZE);
						break;
					}
					if (explosioncount[i] == changeframenum[3]) {
						m_playerstock_Sprite[i]->Init("Assets/Image/balloon.orange2.dds", nsUIDConstant::STOCK_UI_SIZE, nsUIDConstant::STOCK_UI_SIZE);
						explosioncount[i] = 0;
						m_PlDecStock[i] = false;
						break;
					}
					break;
				case 5:
					explosioncount[i] += 1;
					if (explosioncount[i] == changeframenum[0]) {
						m_playerstock_Sprite[i]->Init("Assets/Image/balloon.pink4.dds", nsUIDConstant::STOCK_UI_SIZE, nsUIDConstant::STOCK_UI_SIZE);
						break;
					}
					if (explosioncount[i] == changeframenum[1]) {
						m_playerstock_Sprite[i]->Init("Assets/Image/balloon.pink5.dds", nsUIDConstant::STOCK_UI_SIZE, nsUIDConstant::STOCK_UI_SIZE);
						break;
					}
					if (explosioncount[i] == changeframenum[2]) {
						m_playerstock_Sprite[i]->Init("Assets/Image/balloon.pink6.dds", nsUIDConstant::STOCK_UI_SIZE, nsUIDConstant::STOCK_UI_SIZE);
						break;
					}
					if (explosioncount[i] == changeframenum[3]) {
						m_playerstock_Sprite[i]->Init("Assets/Image/balloon.pink2.dds", nsUIDConstant::STOCK_UI_SIZE, nsUIDConstant::STOCK_UI_SIZE);
						explosioncount[i] = 0;
						m_PlDecStock[i] = false;
						break;
					}
					break;
				case 6:
					explosioncount[i] += 1;
					if (explosioncount[i] == changeframenum[0]) {
						m_playerstock_Sprite[i]->Init("Assets/Image/balloon.gray4.dds", nsUIDConstant::STOCK_UI_SIZE, nsUIDConstant::STOCK_UI_SIZE);
						break;
					}
					if (explosioncount[i] == changeframenum[1]) {
						m_playerstock_Sprite[i]->Init("Assets/Image/balloon.gray5.dds", nsUIDConstant::STOCK_UI_SIZE, nsUIDConstant::STOCK_UI_SIZE);
						break;
					}
					if (explosioncount[i] == changeframenum[2]) {
						m_playerstock_Sprite[i]->Init("Assets/Image/balloon.gray6.dds", nsUIDConstant::STOCK_UI_SIZE, nsUIDConstant::STOCK_UI_SIZE);
						break;
					}
					if (explosioncount[i] == changeframenum[3]) {
						m_playerstock_Sprite[i]->Init("Assets/Image/balloon.gray2.dds", nsUIDConstant::STOCK_UI_SIZE, nsUIDConstant::STOCK_UI_SIZE);
						explosioncount[i] = 0;
						m_PlDecStock[i] = false;
						break;
					}
					break;
				case 7:
					explosioncount[i] += 1;
					if (explosioncount[i] == changeframenum[0]) {
						m_playerstock_Sprite[i]->Init("Assets/Image/balloon.purple4.dds", nsUIDConstant::STOCK_UI_SIZE, nsUIDConstant::STOCK_UI_SIZE);
						break;
					}
					if (explosioncount[i] == changeframenum[1]) {
						m_playerstock_Sprite[i]->Init("Assets/Image/balloon.purple5.dds", nsUIDConstant::STOCK_UI_SIZE, nsUIDConstant::STOCK_UI_SIZE);
						break;
					}
					if (explosioncount[i] == changeframenum[2]) {
						m_playerstock_Sprite[i]->Init("Assets/Image/balloon.purple6.dds", nsUIDConstant::STOCK_UI_SIZE, nsUIDConstant::STOCK_UI_SIZE);
						break;
					}
					if (explosioncount[i] == changeframenum[3]) {
						m_playerstock_Sprite[i]->Init("Assets/Image/balloon.purple2.dds", nsUIDConstant::STOCK_UI_SIZE, nsUIDConstant::STOCK_UI_SIZE);
						explosioncount[i] = 0;
						m_PlDecStock[i] = false;
						break;
					}
					break;
				}
			}
		}
	}

	void UIDisplay::SetPlayerStock(int stock, int plNum)
	{
		m_playerstock_FontRender[plNum]->SetText(L"x" + std::to_wstring(stock));

		m_PlDecStock[plNum] = true;

	}
	void UIDisplay::MinusDisplay(int pnum)
	{
		if (m_isMinus[pnum]) {
			m_pointMinusLoop[pnum]++;
			m_minusPoint_Sprite[pnum]->SetScale(Vector3::One);
			if (m_pointMinusLoop[pnum] > 100) {
				m_isMinus[pnum] = false;
				m_pointMinusLoop[pnum] = 0;
				m_minusPoint_Sprite[pnum]->SetScale(Vector3::Zero);
			}
		}
	}
}