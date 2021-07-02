#include "stdafx.h"
#include "UIDisplay.h"
#include "GameScene.h"
#include "Player.h"
UIDisplay::~UIDisplay()
{

}
bool UIDisplay::Start()
{
	QueryGOs<Player>("player", [this](Player* player)->bool {
		for (int i = 0; i < 8; i++) {
			if (player->GetPlayerNum() == i) {				
				m_playerUI_Sprite[i] = NewGO<SpriteRender>(0);	
				m_playerstock_Sprite[i] = NewGO<SpriteRender>(0);
				m_playerstock_FontRender[i] = NewGO<FontRender>(0);
				
				switch (i)
				{
				case 0:
					m_playerUI_Sprite[i]->Init("Assets/Image/ballooooooon.red.dds", 252, 420);
					m_playerstock_Sprite[i]->Init("Assets/Image/balloon.red2.dds", 128, 128);
					break;
				case 1:
					m_playerUI_Sprite[i]->Init("Assets/Image/ballooooooon.blue.dds", 252, 420);
					m_playerstock_Sprite[i]->Init("Assets/Image/balloon.blue2.dds", 128, 128);
					break;
				case 2:
					m_playerUI_Sprite[i]->Init("Assets/Image/ballooooooon.green.dds", 252, 420);
					m_playerstock_Sprite[i]->Init("Assets/Image/balloon.green2.dds", 128, 128);
					break;
				case 3:
					m_playerUI_Sprite[i]->Init("Assets/Image/ballooooooon.yellow.dds", 252, 420);
					m_playerstock_Sprite[i]->Init("Assets/Image/balloon.yellow2.dds", 128, 128);
					break;
				case 4:
					m_playerUI_Sprite[i]->Init("Assets/Image/ballooooooon.orange.dds", 252, 420);
					m_playerstock_Sprite[i]->Init("Assets/Image/balloon.orange2.dds", 128, 128);
					break;
				case 5:
					m_playerUI_Sprite[i]->Init("Assets/Image/ballooooooon.pink.dds", 252, 420);
					m_playerstock_Sprite[i]->Init("Assets/Image/balloon.pink2.dds", 128, 128);
					break;
				case 6:
					m_playerUI_Sprite[i]->Init("Assets/Image/ballooooooon.gray.dds", 252, 420);
					m_playerstock_Sprite[i]->Init("Assets/Image/balloon.gray2.dds", 128, 128);
					break;
				case 7:
					m_playerUI_Sprite[i]->Init("Assets/Image/ballooooooon.purple.dds", 252, 420);
					m_playerstock_Sprite[i]->Init("Assets/Image/balloon.purple2.dds", 128, 128);
					break;
				default:
					break;
				}
				
				m_playerUI_Sprite[i]->SetScale(PLAYER_UI_SIZE);
				m_playerUI_Sprite[i]->SetPosition(m_playerUI_Pos[i]);

				m_playerstock_Sprite[i]->SetScale(PLAYER_STOCK_SIZE);
				m_playerstock_Sprite[i]->SetPosition(m_playerstock_Pos[i]);

				m_playerstock_FontRender[i]->SetColor(STOCKNUM_COLOR);
				m_playerstock_FontRender[i]->SetPosition(PL_STOCKNUM_POS[i]);
				m_playerstock_FontRender[i]->SetScale({ STOCKNUM_SIZE });
				break;
			}
		}
		
		return true;
		});

	return true;
}
void UIDisplay::Update()
{
	QueryGOs<Player>("player", [this](Player* player)->bool {
		for (int i = 0; i < 8; i++) {
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

	for (int i = 0; i < 8; i++) {
		if (m_PlDecStock[i] == true) {
			switch (i)
			{
			case 0:
				explosioncount[i] += 1;
				if (explosioncount[i] == changeframenum[0]) {
					m_playerstock_Sprite[i]->Init("Assets/Image/balloon.red4.dds", 128, 128);
					break;
				}
				if (explosioncount[i] == changeframenum[1]) {
					m_playerstock_Sprite[i]->Init("Assets/Image/balloon.red5.dds", 128, 128);
					break;
				}
				if (explosioncount[i] == changeframenum[2]) {
					m_playerstock_Sprite[i]->Init("Assets/Image/balloon.red6.dds", 128, 128);
					break;
				}
				if (explosioncount[i] == changeframenum[3]) {
					m_playerstock_Sprite[i]->Init("Assets/Image/balloon.red2.dds", 128, 128);
					explosioncount[i] = 0;
					m_PlDecStock[i] = false;
					break;
				}
				break;
			case 1:
				explosioncount[i] += 1;
				if (explosioncount[i] == changeframenum[0]) {
					m_playerstock_Sprite[i]->Init("Assets/Image/balloon.blue4.dds", 128, 128);
					break;
				}
				if (explosioncount[i] == changeframenum[1]) {
					m_playerstock_Sprite[i]->Init("Assets/Image/balloon.blue5.dds", 128, 128);
					break;
				}
				if (explosioncount[i] == changeframenum[2]) {
					m_playerstock_Sprite[i]->Init("Assets/Image/balloon.blue6.dds", 128, 128);
					break;
				}
				if (explosioncount[i] == changeframenum[3]) {
					m_playerstock_Sprite[i]->Init("Assets/Image/balloon.blue2.dds", 128, 128);
					explosioncount[i] = 0;
					m_PlDecStock[i] = false;
					break;
				}
				break;
			case 2:
				explosioncount[i] += 1;
				if (explosioncount[i] == changeframenum[0]) {
					m_playerstock_Sprite[i]->Init("Assets/Image/balloon.red4.dds", 128, 128);
					break;
				}
				if (explosioncount[i] == changeframenum[1]) {
					m_playerstock_Sprite[i]->Init("Assets/Image/balloon.red5.dds", 128, 128);
					break;
				}
				if (explosioncount[i] == changeframenum[2]) {
					m_playerstock_Sprite[i]->Init("Assets/Image/balloon.red6.dds", 128, 128);
					break;
				}
				if (explosioncount[i] == changeframenum[3]) {
					m_playerstock_Sprite[i]->Init("Assets/Image/balloon.red2.dds", 128, 128);
					explosioncount[i] = 0;
					m_PlDecStock[i] = false;
					break;
				}
				break;
			case 3:
				explosioncount[i] += 1;
				if (explosioncount[i] == changeframenum[0]) {
					m_playerstock_Sprite[i]->Init("Assets/Image/balloon.red4.dds", 128, 128);
					break;
				}
				if (explosioncount[i] == changeframenum[1]) {
					m_playerstock_Sprite[i]->Init("Assets/Image/balloon.red5.dds", 128, 128);
					break;
				}
				if (explosioncount[i] == changeframenum[2]) {
					m_playerstock_Sprite[i]->Init("Assets/Image/balloon.red6.dds", 128, 128);
					break;
				}
				if (explosioncount[i] == changeframenum[3]) {
					m_playerstock_Sprite[i]->Init("Assets/Image/balloon.red2.dds", 128, 128);
					explosioncount[i] = 0;
					m_PlDecStock[i] = false;
					break;
				}
				break;
			case 4:
				explosioncount[i] += 1;
				if (explosioncount[i] == changeframenum[0]) {
					m_playerstock_Sprite[i]->Init("Assets/Image/balloon.red4.dds", 128, 128);
					break;
				}
				if (explosioncount[i] == changeframenum[1]) {
					m_playerstock_Sprite[i]->Init("Assets/Image/balloon.red5.dds", 128, 128);
					break;
				}
				if (explosioncount[i] == changeframenum[2]) {
					m_playerstock_Sprite[i]->Init("Assets/Image/balloon.red6.dds", 128, 128);
					break;
				}
				if (explosioncount[i] == changeframenum[3]) {
					m_playerstock_Sprite[i]->Init("Assets/Image/balloon.red2.dds", 128, 128);
					explosioncount[i] = 0;
					m_PlDecStock[i] = false;
					break;
				}
				break;
			case 5:
				explosioncount[i] += 1;
				if (explosioncount[i] == changeframenum[0]) {
					m_playerstock_Sprite[i]->Init("Assets/Image/balloon.red4.dds", 128, 128);
					break;
				}
				if (explosioncount[i] == changeframenum[1]) {
					m_playerstock_Sprite[i]->Init("Assets/Image/balloon.red5.dds", 128, 128);
					break;
				}
				if (explosioncount[i] == changeframenum[2]){
					m_playerstock_Sprite[i]->Init("Assets/Image/balloon.red6.dds", 128, 128);
					break;
				}
				if (explosioncount[i] == changeframenum[3]) {
					m_playerstock_Sprite[i]->Init("Assets/Image/balloon.red2.dds", 128, 128);
					explosioncount[i] = 0;
					m_PlDecStock[i] = false;
					break;
				}
				break;
			case 6:
				explosioncount[i] += 1;
				if (explosioncount[i] == changeframenum[0]) {
					m_playerstock_Sprite[i]->Init("Assets/Image/balloon.red4.dds", 128, 128);
					break;
				}
				if (explosioncount[i] == changeframenum[1]) {
					m_playerstock_Sprite[i]->Init("Assets/Image/balloon.red5.dds", 128, 128);
					break;
				}
				if (explosioncount[i] == changeframenum[2]) {
					m_playerstock_Sprite[i]->Init("Assets/Image/balloon.red6.dds", 128, 128);
					break;
				}
				if (explosioncount[i] == changeframenum[3]) {
					m_playerstock_Sprite[i]->Init("Assets/Image/balloon.red2.dds", 128, 128);
					explosioncount[i] = 0;
					m_PlDecStock[i] = false;
					break;
				}
				break;
			case 7:
				explosioncount[i] += 1;
				if (explosioncount[i] == changeframenum[0]) {
					m_playerstock_Sprite[i]->Init("Assets/Image/balloon.red4.dds", 128, 128);
					break;
				}
				if (explosioncount[i] == changeframenum[1]) {
					m_playerstock_Sprite[i]->Init("Assets/Image/balloon.red5.dds", 128, 128);
					break;
				}
				if (explosioncount[i] == changeframenum[2]) {
					m_playerstock_Sprite[i]->Init("Assets/Image/balloon.red6.dds", 128, 128);
					break;
				}
				if (explosioncount[i] == changeframenum[3]) {
					m_playerstock_Sprite[i]->Init("Assets/Image/balloon.red2.dds", 128, 128);
					explosioncount[i] = 0;
					m_PlDecStock[i] = false;
					break;
				}
				break;
			}
		}
		for (int i = 0; i < 8; i++) {
			if (m_PlDeath[i] == true) {
				m_playerstock_FontRender[i]->SetText(m_stocknum[0]);
			}
		}
	}


	/*QueryGOs<Player>("player", [this](Player* player)->bool {
		if (player->GetPlayerNum() == 0)
		{

			if (loopcount == 0) {
				m_player1stock_Sprite->Init("Assets/Image/balloon.red1.dds", 128, 128);
				m_player1stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
				m_player1stock_Sprite->SetPosition(m_player1stock_Pos);
			}
			if (loopcount == 10) {
				m_player1stock_Sprite->Init("Assets/Image/balloon.red2.dds", 128, 128);
				m_player1stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
				m_player1stock_Sprite->SetPosition(m_player1stock_Pos);
			}
			if (loopcount == 20) {
				m_player1stock_Sprite->Init("Assets/Image/balloon.red3.dds", 128, 128);
				m_player1stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
				m_player1stock_Sprite->SetPosition(m_player1stock_Pos);
			}
			if (loopcount == 30) {
				m_player1stock_Sprite->Init("Assets/Image/balloon.red2.dds", 128, 128);
				m_player1stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
				m_player1stock_Sprite->SetPosition(m_player1stock_Pos);
			}
		}
		if (player->GetPlayerNum() == 1)
		{
			if (loopcount == 0) {
				m_player2stock_Sprite->Init("Assets/Image/balloon.blue1.dds", 128, 128);
				m_player2stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
				m_player2stock_Sprite->SetPosition(m_player2stock_Pos);
			}
			if (loopcount == 10) {
				m_player2stock_Sprite->Init("Assets/Image/balloon.blue2.dds", 128, 128);
				m_player2stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
				m_player2stock_Sprite->SetPosition(m_player2stock_Pos);
			}
			if (loopcount == 20) {
				m_player2stock_Sprite->Init("Assets/Image/balloon.blue3.dds", 128, 128);
				m_player2stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
				m_player2stock_Sprite->SetPosition(m_player2stock_Pos);
			}
			if (loopcount == 30) {
				m_player2stock_Sprite->Init("Assets/Image/balloon.blue2.dds", 128, 128);
				m_player2stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
				m_player2stock_Sprite->SetPosition(m_player2stock_Pos);
			}
		}
		if (player->GetPlayerNum() == 2)
		{
			if (loopcount == 0) {
				m_player3stock_Sprite->Init("Assets/Image/balloon.green1.dds", 128, 128);
				m_player3stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
				m_player3stock_Sprite->SetPosition(m_player3stock_Pos);
			}
			if (loopcount == 10) {
				m_player3stock_Sprite->Init("Assets/Image/balloon.green2.dds", 128, 128);
				m_player3stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
				m_player3stock_Sprite->SetPosition(m_player3stock_Pos);
			}
			if (loopcount == 20) {
				m_player3stock_Sprite->Init("Assets/Image/balloon.green3.dds", 128, 128);
				m_player3stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
				m_player3stock_Sprite->SetPosition(m_player3stock_Pos);
			}
			if (loopcount == 30) {
				m_player3stock_Sprite->Init("Assets/Image/balloon.green2.dds", 128, 128);
				m_player3stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
				m_player3stock_Sprite->SetPosition(m_player3stock_Pos);
			}
		}
		if (player->GetPlayerNum() == 3)
		{
			if (loopcount == 0) {
				m_player4stock_Sprite->Init("Assets/Image/balloon.yellow1.dds", 128, 128);
				m_player4stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
				m_player4stock_Sprite->SetPosition(m_player4stock_Pos);
			}
			if (loopcount == 10) {
				m_player4stock_Sprite->Init("Assets/Image/balloon.yellow2.dds", 128, 128);
				m_player4stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
				m_player4stock_Sprite->SetPosition(m_player4stock_Pos);
			}
			if (loopcount == 20) {
				m_player4stock_Sprite->Init("Assets/Image/balloon.yellow3.dds", 128, 128);
				m_player4stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
				m_player4stock_Sprite->SetPosition(m_player4stock_Pos);
			}
			if (loopcount == 30) {
				m_player4stock_Sprite->Init("Assets/Image/balloon.yellow2.dds", 128, 128);
				m_player4stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
				m_player4stock_Sprite->SetPosition(m_player4stock_Pos);
			}
		}
		if (player->GetPlayerNum() == 4)
		{
			if (loopcount == 0) {
				m_player5stock_Sprite->Init("Assets/Image/balloon.orange1.dds", 128, 128);
				m_player5stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
				m_player5stock_Sprite->SetPosition(m_player5stock_Pos);
			}
			if (loopcount == 10) {
				m_player5stock_Sprite->Init("Assets/Image/balloon.orange2.dds", 128, 128);
				m_player5stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
				m_player5stock_Sprite->SetPosition(m_player5stock_Pos);
			}
			if (loopcount == 20) {
				m_player5stock_Sprite->Init("Assets/Image/balloon.orange3.dds", 128, 128);
				m_player5stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
				m_player5stock_Sprite->SetPosition(m_player5stock_Pos);
			}
			if (loopcount == 30) {
				m_player5stock_Sprite->Init("Assets/Image/balloon.orange2.dds", 128, 128);
				m_player5stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
				m_player5stock_Sprite->SetPosition(m_player5stock_Pos);
			}
		}
		if (player->GetPlayerNum() == 5)
		{
			if (loopcount == 0) {
				m_player6stock_Sprite->Init("Assets/Image/balloon.pink1.dds", 128, 128);
				m_player6stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
				m_player6stock_Sprite->SetPosition(m_player6stock_Pos);
			}
			if (loopcount == 10) {
				m_player6stock_Sprite->Init("Assets/Image/balloon.pink2.dds", 128, 128);
				m_player6stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
				m_player6stock_Sprite->SetPosition(m_player6stock_Pos);
			}
			if (loopcount == 20) {
				m_player6stock_Sprite->Init("Assets/Image/balloon.pink3.dds", 128, 128);
				m_player6stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
				m_player6stock_Sprite->SetPosition(m_player6stock_Pos);
			}
			if (loopcount == 30) {
				m_player6stock_Sprite->Init("Assets/Image/balloon.pink2.dds", 128, 128);
				m_player6stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
				m_player6stock_Sprite->SetPosition(m_player6stock_Pos);
			}
		}
		if (player->GetPlayerNum() == 6)
		{
			if (loopcount == 0) {
				m_player7stock_Sprite->Init("Assets/Image/balloon.gray1.dds", 128, 128);
				m_player7stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
				m_player7stock_Sprite->SetPosition(m_player7stock_Pos);
			}
			if (loopcount == 10) {
				m_player7stock_Sprite->Init("Assets/Image/balloon.gray2.dds", 128, 128);
				m_player7stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
				m_player7stock_Sprite->SetPosition(m_player7stock_Pos);
			}
			if (loopcount == 20) {
				m_player7stock_Sprite->Init("Assets/Image/balloon.gray3.dds", 128, 128);
				m_player7stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
				m_player7stock_Sprite->SetPosition(m_player7stock_Pos);
			}
			if (loopcount == 30) {
				m_player7stock_Sprite->Init("Assets/Image/balloon.gray2.dds", 128, 128);
				m_player7stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
				m_player7stock_Sprite->SetPosition(m_player7stock_Pos);
			}
		}
		if (player->GetPlayerNum() == 7)
		{
			if (loopcount == 0) {
				m_player8stock_Sprite->Init("Assets/Image/balloon.purple1.dds", 128, 128);
				m_player8stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
				m_player8stock_Sprite->SetPosition(m_player8stock_Pos);
			}
			if (loopcount == 10) {
				m_player8stock_Sprite->Init("Assets/Image/balloon.purple2.dds", 128, 128);
				m_player8stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
				m_player8stock_Sprite->SetPosition(m_player8stock_Pos);
			}
			if (loopcount == 20) {
				m_player8stock_Sprite->Init("Assets/Image/balloon.purple3.dds", 128, 128);
				m_player8stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
				m_player8stock_Sprite->SetPosition(m_player8stock_Pos);
			}
			if (loopcount == 30) {
				m_player8stock_Sprite->Init("Assets/Image/balloon.purple2.dds", 128, 128);
				m_player8stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
				m_player8stock_Sprite->SetPosition(m_player8stock_Pos);
			}
		}
		return true;
		});*/
	loopcount += 1;
	if (loopcount == 40) {
		loopcount = 0;
	}
}
 