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
			m_player1stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
			m_player1stock_Sprite->SetPosition(m_player1stock_Pos);
		}
		else if (player->GetPlayerNum() == 1) {
			m_player2UI_Sprite = NewGO<SpriteRender>(0);
			m_player2UI_Sprite->Init("Assets/Image/ballooooooon.blue.dds", 252, 420);
			m_player2UI_Sprite->SetScale(PLAYER_UI_SIZE);
			m_player2UI_Sprite->SetPosition(m_player2UI_Pos);

			m_player2stock_Sprite = NewGO<SpriteRender>(0);
			m_player2stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
			m_player2stock_Sprite->SetPosition(m_player2stock_Pos);

		}
		else if (player->GetPlayerNum() == 2) {
			m_player3UI_Sprite = NewGO<SpriteRender>(0);
			m_player3UI_Sprite->Init("Assets/Image/ballooooooon.green.dds", 252, 420);
			m_player3UI_Sprite->SetScale(PLAYER_UI_SIZE);
			m_player3UI_Sprite->SetPosition(m_player3UI_Pos);

			m_player3stock_Sprite = NewGO<SpriteRender>(0);
			m_player3stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
			m_player3stock_Sprite->SetPosition(m_player3stock_Pos);
		}
		else if (player->GetPlayerNum() == 3) {
			m_player4UI_Sprite = NewGO<SpriteRender>(0);
			m_player4UI_Sprite->Init("Assets/Image/ballooooooon.yellow.dds", 252, 420);
			m_player4UI_Sprite->SetScale(PLAYER_UI_SIZE);
			m_player4UI_Sprite->SetPosition(m_player4UI_Pos);

			m_player4stock_Sprite = NewGO<SpriteRender>(0);
			m_player4stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
			m_player4stock_Sprite->SetPosition(m_player4stock_Pos);
		}
		else if (player->GetPlayerNum() == 4) {
			m_player5UI_Sprite = NewGO<SpriteRender>(0);
			m_player5UI_Sprite->Init("Assets/Image/ballooooooon.orange.dds", 252, 420);
			m_player5UI_Sprite->SetScale(PLAYER_UI_SIZE);
			m_player5UI_Sprite->SetPosition(m_player5UI_Pos);

			m_player5stock_Sprite = NewGO<SpriteRender>(0);
			m_player5stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
			m_player5stock_Sprite->SetPosition(m_player5stock_Pos);
		}
		else if (player->GetPlayerNum() == 5) {
			m_player6UI_Sprite = NewGO<SpriteRender>(0);
			m_player6UI_Sprite->Init("Assets/Image/ballooooooon.pink.dds", 252, 420);
			m_player6UI_Sprite->SetScale(PLAYER_UI_SIZE);
			m_player6UI_Sprite->SetPosition(m_player6UI_Pos);

			m_player6stock_Sprite = NewGO<SpriteRender>(0);
			m_player6stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
			m_player6stock_Sprite->SetPosition(m_player6stock_Pos);
		}
		else if (player->GetPlayerNum() == 6) {
			m_player7UI_Sprite = NewGO<SpriteRender>(0);
			m_player7UI_Sprite->Init("Assets/Image/ballooooooon.gray.dds", 252, 420);
			m_player7UI_Sprite->SetScale(PLAYER_UI_SIZE);
			m_player7UI_Sprite->SetPosition(m_player7UI_Pos);

			m_player7stock_Sprite = NewGO<SpriteRender>(0);
			m_player7stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
			m_player7stock_Sprite->SetPosition(m_player7stock_Pos);
		}
		else if (player->GetPlayerNum() == 7) {
			m_player8UI_Sprite = NewGO<SpriteRender>(0);
			m_player8UI_Sprite->Init("Assets/Image/ballooooooon.purple.dds", 252, 420);
			m_player8UI_Sprite->SetScale(PLAYER_UI_SIZE);
			m_player8UI_Sprite->SetPosition(m_player8UI_Pos);

			m_player8stock_Sprite = NewGO<SpriteRender>(0);
			m_player8stock_Sprite->SetScale(PLAYER_STOCK_SIZE);
			m_player8stock_Sprite->SetPosition(m_player8stock_Pos);
		}
		return true;
		});

	return true;
}
void UIDisplay::Update()
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
	
	loopcount += 1;
	if (loopcount == 40) {
		loopcount = 0;
	}
}
