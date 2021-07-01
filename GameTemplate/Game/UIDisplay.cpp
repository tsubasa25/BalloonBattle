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
		if (player->GetPlayerNum() == 0) {
			m_player1UI_Sprite = NewGO<SpriteRender>(0);
			m_player1UI_Sprite->Init("Assets/Image/ballooooooon.red.dds", 252, 420);
			m_player1UI_Sprite->SetScale(PLAYER_UI_SIZE);
			m_player1UI_Sprite->SetPosition(m_player1UI_Pos);

			m_player1stock_Sprite = NewGO<SpriteRender>(0); 
			m_player1stock_Sprite->Init("Assets/Image/balloon.red2.dds", 128, 128);
			m_player1stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
			m_player1stock_Sprite->SetPosition(m_player1stock_Pos);

			m_player1stock_FontRender = NewGO<FontRender>(0);
			m_player1stock_FontRender->SetColor(STOCKNUM_COLOR);
			m_player1stock_FontRender->SetPosition(PL1_STOCKNUM_POS);
			m_player1stock_FontRender->SetScale({ STOCKNUM_SIZE });
		}
		else if (player->GetPlayerNum() == 1) {
			m_player2UI_Sprite = NewGO<SpriteRender>(0);
			m_player2UI_Sprite->Init("Assets/Image/ballooooooon.blue.dds", 252, 420);
			m_player2UI_Sprite->SetScale(PLAYER_UI_SIZE);
			m_player2UI_Sprite->SetPosition(m_player2UI_Pos);

			m_player2stock_Sprite = NewGO<SpriteRender>(0);
			m_player2stock_Sprite->Init("Assets/Image/balloon.blue2.dds", 128, 128);
			m_player2stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
			m_player2stock_Sprite->SetPosition(m_player2stock_Pos);

			m_player2stock_FontRender = NewGO<FontRender>(0);
			m_player2stock_FontRender->SetColor(STOCKNUM_COLOR);
			m_player2stock_FontRender->SetPosition(PL2_STOCKNUM_POS);
			m_player2stock_FontRender->SetScale({ STOCKNUM_SIZE });
		}
		else if (player->GetPlayerNum() == 2) {
			m_player3UI_Sprite = NewGO<SpriteRender>(0);
			m_player3UI_Sprite->Init("Assets/Image/ballooooooon.green.dds", 252, 420);
			m_player3UI_Sprite->SetScale(PLAYER_UI_SIZE);
			m_player3UI_Sprite->SetPosition(m_player3UI_Pos);

			m_player3stock_Sprite = NewGO<SpriteRender>(0);
			m_player3stock_Sprite->Init("Assets/Image/balloon.green2.dds", 128, 128);
			m_player3stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
			m_player3stock_Sprite->SetPosition(m_player3stock_Pos);

			m_player3stock_FontRender = NewGO<FontRender>(0);
			m_player3stock_FontRender->SetColor(STOCKNUM_COLOR);
			m_player3stock_FontRender->SetPosition(PL3_STOCKNUM_POS);
			m_player3stock_FontRender->SetScale({ STOCKNUM_SIZE });
		}
		else if (player->GetPlayerNum() == 3) {
			m_player4UI_Sprite = NewGO<SpriteRender>(0);
			m_player4UI_Sprite->Init("Assets/Image/ballooooooon.yellow.dds", 252, 420);
			m_player4UI_Sprite->SetScale(PLAYER_UI_SIZE);
			m_player4UI_Sprite->SetPosition(m_player4UI_Pos);

			m_player4stock_Sprite = NewGO<SpriteRender>(0);
			m_player4stock_Sprite->Init("Assets/Image/balloon.yellow2.dds", 128, 128);
			m_player4stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
			m_player4stock_Sprite->SetPosition(m_player4stock_Pos);

			m_player4stock_FontRender = NewGO<FontRender>(0);
			m_player4stock_FontRender->SetColor(STOCKNUM_COLOR);
			m_player4stock_FontRender->SetPosition(PL4_STOCKNUM_POS);
			m_player4stock_FontRender->SetScale({ STOCKNUM_SIZE });
		}
		else if (player->GetPlayerNum() == 4) {
			m_player5UI_Sprite = NewGO<SpriteRender>(0);
			m_player5UI_Sprite->Init("Assets/Image/ballooooooon.orange.dds", 252, 420);
			m_player5UI_Sprite->SetScale(PLAYER_UI_SIZE);
			m_player5UI_Sprite->SetPosition(m_player5UI_Pos);

			m_player5stock_Sprite = NewGO<SpriteRender>(0);
			m_player5stock_Sprite->Init("Assets/Image/balloon.orange2.dds", 128, 128);
			m_player5stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
			m_player5stock_Sprite->SetPosition(m_player5stock_Pos);

			m_player5stock_FontRender = NewGO<FontRender>(0);
			m_player5stock_FontRender->SetColor(STOCKNUM_COLOR);
			m_player5stock_FontRender->SetPosition(PL5_STOCKNUM_POS);
			m_player5stock_FontRender->SetScale({ STOCKNUM_SIZE });
		}
		else if (player->GetPlayerNum() == 5) {
			m_player6UI_Sprite = NewGO<SpriteRender>(0);
			m_player6UI_Sprite->Init("Assets/Image/ballooooooon.pink.dds", 252, 420);
			m_player6UI_Sprite->SetScale(PLAYER_UI_SIZE);
			m_player6UI_Sprite->SetPosition(m_player6UI_Pos);

			m_player6stock_Sprite = NewGO<SpriteRender>(0);
			m_player6stock_Sprite->Init("Assets/Image/balloon.pink2.dds", 128, 128);
			m_player6stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
			m_player6stock_Sprite->SetPosition(m_player6stock_Pos);

			m_player6stock_FontRender = NewGO<FontRender>(0);
			m_player6stock_FontRender->SetColor(STOCKNUM_COLOR);
			m_player6stock_FontRender->SetPosition(PL6_STOCKNUM_POS);
			m_player6stock_FontRender->SetScale({ STOCKNUM_SIZE });
		}
		else if (player->GetPlayerNum() == 6) {
			m_player7UI_Sprite = NewGO<SpriteRender>(0);
			m_player7UI_Sprite->Init("Assets/Image/ballooooooon.gray.dds", 252, 420);
			m_player7UI_Sprite->SetScale(PLAYER_UI_SIZE);
			m_player7UI_Sprite->SetPosition(m_player7UI_Pos);

			m_player7stock_Sprite = NewGO<SpriteRender>(0);
			m_player7stock_Sprite->Init("Assets/Image/balloon.gray2.dds", 128, 128);
			m_player7stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
			m_player7stock_Sprite->SetPosition(m_player7stock_Pos);

			m_player7stock_FontRender = NewGO<FontRender>(0);
			m_player7stock_FontRender->SetColor(STOCKNUM_COLOR);
			m_player7stock_FontRender->SetPosition(PL7_STOCKNUM_POS);
			m_player7stock_FontRender->SetScale({ STOCKNUM_SIZE });
		}
		else if (player->GetPlayerNum() == 7) {
			m_player8UI_Sprite = NewGO<SpriteRender>(0);
			m_player8UI_Sprite->Init("Assets/Image/ballooooooon.purple.dds", 252, 420);
			m_player8UI_Sprite->SetScale(PLAYER_UI_SIZE);
			m_player8UI_Sprite->SetPosition(m_player8UI_Pos);

			m_player8stock_Sprite = NewGO<SpriteRender>(0);
			m_player8stock_Sprite->Init("Assets/Image/balloon.purple2.dds", 128, 128);
			m_player8stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
			m_player8stock_Sprite->SetPosition(m_player8stock_Pos);

			m_player8stock_FontRender = NewGO<FontRender>(0);
			m_player8stock_FontRender->SetColor(STOCKNUM_COLOR);
			m_player8stock_FontRender->SetPosition(PL8_STOCKNUM_POS);
			m_player8stock_FontRender->SetScale({ STOCKNUM_SIZE });
		}
		return true;
		});

	return true;
}
void UIDisplay::Update()
{
	QueryGOs<Player>("player", [this](Player* player)->bool {
		if (player->GetPlayerNum() == 0) {
			if (player->GetPlayerStock() == 5) {
				m_player1stock_FontRender->SetText(m_stocknum5);
			}
			if (player->GetPlayerStock() == 4) {
				m_player1stock_FontRender->SetText(m_stocknum4);
			}
			if (player->GetPlayerStock() == 3) {
				m_player1stock_FontRender->SetText(m_stocknum3);
			}
			if (player->GetPlayerStock() == 2) {
				m_player1stock_FontRender->SetText(m_stocknum2);
			}
			if (player->GetPlayerStock() == 1) {
				m_player1stock_FontRender->SetText(m_stocknum1);
			}
			if (player->GetPlayerStock() == 0) {
				m_player1stock_FontRender->SetText(m_stocknum1);
			}
		}
		if (player->GetPlayerNum() == 1) {
			if (player->GetPlayerStock() == 5) {
				m_player2stock_FontRender->SetText(m_stocknum5);
			}
			if (player->GetPlayerStock() == 4) {
				m_player2stock_FontRender->SetText(m_stocknum4);
			}
			if (player->GetPlayerStock() == 3) {
				m_player2stock_FontRender->SetText(m_stocknum3);
			}
			if (player->GetPlayerStock() == 2) {
				m_player2stock_FontRender->SetText(m_stocknum2);
			}
			if (player->GetPlayerStock() == 1) {
				m_player2stock_FontRender->SetText(m_stocknum1);
			}
			if (player->GetPlayerStock() == 0) {
				m_player2stock_FontRender->SetText(m_stocknum1);
			}
		}
		if (player->GetPlayerNum() == 2) {
			if (player->GetPlayerStock() == 5) {
				m_player3stock_FontRender->SetText(m_stocknum5);
			}
			if (player->GetPlayerStock() == 4) {
				m_player3stock_FontRender->SetText(m_stocknum4);
			}
			if (player->GetPlayerStock() == 3) {
				m_player3stock_FontRender->SetText(m_stocknum3);
			}
			if (player->GetPlayerStock() == 2) {
				m_player3stock_FontRender->SetText(m_stocknum2);
			}
			if (player->GetPlayerStock() == 1) {
				m_player3stock_FontRender->SetText(m_stocknum1);
			}
			if (player->GetPlayerStock() == 0) {
				m_player3stock_FontRender->SetText(m_stocknum1);
			}
		}
		if (player->GetPlayerNum() == 3) {
			if (player->GetPlayerStock() == 5) {
				m_player4stock_FontRender->SetText(m_stocknum5);
			}
			if (player->GetPlayerStock() == 4) {
				m_player4stock_FontRender->SetText(m_stocknum4);
			}
			if (player->GetPlayerStock() == 3) {
				m_player4stock_FontRender->SetText(m_stocknum3);
			}
			if (player->GetPlayerStock() == 2) {
				m_player4stock_FontRender->SetText(m_stocknum2);
			}
			if (player->GetPlayerStock() == 1) {
				m_player4stock_FontRender->SetText(m_stocknum1);
			}
			if (player->GetPlayerStock() == 0) {
				m_player4stock_FontRender->SetText(m_stocknum1);
			}
		}
		if (player->GetPlayerNum() == 4) {
			if (player->GetPlayerStock() == 5) {
				m_player5stock_FontRender->SetText(m_stocknum5);
			}
			if (player->GetPlayerStock() == 4) {
				m_player5stock_FontRender->SetText(m_stocknum4);
			}
			if (player->GetPlayerStock() == 3) {
				m_player5stock_FontRender->SetText(m_stocknum3);
			}
			if (player->GetPlayerStock() == 2) {
				m_player5stock_FontRender->SetText(m_stocknum2);
			}
			if (player->GetPlayerStock() == 1) {
				m_player5stock_FontRender->SetText(m_stocknum1);
			}
			if (player->GetPlayerStock() == 0) {
				m_player5stock_FontRender->SetText(m_stocknum1);
			}
		}
		if (player->GetPlayerNum() == 5) {
			if (player->GetPlayerStock() == 5) {
				m_player6stock_FontRender->SetText(m_stocknum5);
			}
			if (player->GetPlayerStock() == 4) {
				m_player6stock_FontRender->SetText(m_stocknum4);
			}
			if (player->GetPlayerStock() == 3) {
				m_player6stock_FontRender->SetText(m_stocknum3);
			}
			if (player->GetPlayerStock() == 2) {
				m_player6stock_FontRender->SetText(m_stocknum2);
			}
			if (player->GetPlayerStock() == 1) {
				m_player6stock_FontRender->SetText(m_stocknum1);
			}
			if (player->GetPlayerStock() == 0) {
				m_player6stock_FontRender->SetText(m_stocknum1);
			}
		}
		if (player->GetPlayerNum() == 6) {
			if (player->GetPlayerStock() == 5) {
				m_player7stock_FontRender->SetText(m_stocknum5);
			}
			if (player->GetPlayerStock() == 4) {
				m_player7stock_FontRender->SetText(m_stocknum4);
			}
			if (player->GetPlayerStock() == 3) {
				m_player7stock_FontRender->SetText(m_stocknum3);
			}
			if (player->GetPlayerStock() == 2) {
				m_player7stock_FontRender->SetText(m_stocknum2);
			}
			if (player->GetPlayerStock() == 1) {
				m_player7stock_FontRender->SetText(m_stocknum1);
			}
			if (player->GetPlayerStock() == 0) {
				m_player7stock_FontRender->SetText(m_stocknum1);
			}
		}
		if (player->GetPlayerNum() == 7) {
			if (player->GetPlayerStock() == 5) {
				m_player8stock_FontRender->SetText(m_stocknum5);
			}
			if (player->GetPlayerStock() == 4) {
				m_player8stock_FontRender->SetText(m_stocknum4);
			}
			if (player->GetPlayerStock() == 3) {
				m_player8stock_FontRender->SetText(m_stocknum3);
			}
			if (player->GetPlayerStock() == 2) {
				m_player8stock_FontRender->SetText(m_stocknum2);
			}
			if (player->GetPlayerStock() == 1) {
				m_player8stock_FontRender->SetText(m_stocknum1);
			}
			if (player->GetPlayerStock() == 0) {
				m_player8stock_FontRender->SetText(m_stocknum1);
			}
		}
		
		return true;
		});

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
 
void UIDisplay::SetPlayerDeath()
{

}