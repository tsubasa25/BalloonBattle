#pragma once
namespace {
	const Vector3 PLAYER1UI_POS = { -575,208,0 };
}
class UIDisplay : public IGameObject
{
public:
	bool Start();
	void Update();
	~UIDisplay();
	void SetPlayerDeath();
	
private:

	const Vector3 PLAYER_UI_SIZE = { 0.3f,0.3f,0.3f };
	const Vector3 PLAYER_STOCK_SIZE = { 0.3f,0.3f,0.3f };
	const float STOCKNUM_SIZE = { 0.9 };
	const Vector4 STOCKNUM_COLOR = { 1.0f,1.0f,1.0f,1.0f };
	const Vector2 PL1_STOCKNUM_POS = { -550,230};
	const Vector2 PL2_STOCKNUM_POS = { 550,230 };
	const Vector2 PL3_STOCKNUM_POS = { -550,55 };
	const Vector2 PL4_STOCKNUM_POS = { 550,55};
	const Vector2 PL5_STOCKNUM_POS = { -550,-125 };
	const Vector2 PL6_STOCKNUM_POS = { 550,-125 };
	const Vector2 PL7_STOCKNUM_POS = { -550,-305 };
	const Vector2 PL8_STOCKNUM_POS = { 550, -305 };

	std::wstring m_stocknum1 = L"x1";
	std::wstring m_stocknum2 = L"x2";
	std::wstring m_stocknum3 = L"x3";
	std::wstring m_stocknum4 = L"x4";
	std::wstring m_stocknum5 = L"x5";

	SpriteRender* m_player1UI_Sprite = nullptr;
	SpriteRender* m_player2UI_Sprite = nullptr;
	SpriteRender* m_player3UI_Sprite = nullptr;
	SpriteRender* m_player4UI_Sprite = nullptr;
	SpriteRender* m_player5UI_Sprite = nullptr;
	SpriteRender* m_player6UI_Sprite = nullptr;
	SpriteRender* m_player7UI_Sprite = nullptr;
	SpriteRender* m_player8UI_Sprite = nullptr;

	SpriteRender* m_player1stock_Sprite = nullptr;
	SpriteRender* m_player2stock_Sprite = nullptr;
	SpriteRender* m_player3stock_Sprite = nullptr;
	SpriteRender* m_player4stock_Sprite = nullptr;
	SpriteRender* m_player5stock_Sprite = nullptr;
	SpriteRender* m_player6stock_Sprite = nullptr;
	SpriteRender* m_player7stock_Sprite = nullptr;
	SpriteRender* m_player8stock_Sprite = nullptr;

	Vector3 m_player1UI_Pos = { -550,290,0 };
	Vector3 m_player2UI_Pos = { 550,290,0 };
	Vector3 m_player3UI_Pos = { -550,115,0 };
	Vector3 m_player4UI_Pos = { 550,115,0 };
	Vector3 m_player5UI_Pos = { -550,-65,0 };
	Vector3 m_player6UI_Pos = { 550,-65,0 };
	Vector3 m_player7UI_Pos = { -550,-245,0 };
	Vector3 m_player8UI_Pos = { 550,-245,0 };

	Vector3 m_player1stock_Pos = { PLAYER1UI_POS };
	Vector3 m_player2stock_Pos = { 525,208,0 };
	Vector3 m_player3stock_Pos = { -575,33,0 };
	Vector3 m_player4stock_Pos = { 525,33,0 };
	Vector3 m_player5stock_Pos = { -575,-147,0 };
	Vector3 m_player6stock_Pos = { 525,-147,0 };
	Vector3 m_player7stock_Pos = { -575,-327,0 };
	Vector3 m_player8stock_Pos = { 525,-327,0 };

	FontRender* m_player1stock_FontRender = nullptr;
	FontRender* m_player2stock_FontRender = nullptr;
	FontRender* m_player3stock_FontRender = nullptr;
	FontRender* m_player4stock_FontRender = nullptr;
	FontRender* m_player5stock_FontRender = nullptr;
	FontRender* m_player6stock_FontRender = nullptr;
	FontRender* m_player7stock_FontRender = nullptr;
	FontRender* m_player8stock_FontRender = nullptr;

	int loopcount = 0;

	bool m_PlDeath[8] = {false,false,false,false,false,false,false,false};
};

