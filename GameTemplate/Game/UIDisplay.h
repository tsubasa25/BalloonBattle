#pragma once
namespace {
	const Vector3 PLAYER1UI_POS = { -550, 290,0 };
	const Vector3 PLAYER2UI_POS = { 550,290,0 };
	const Vector3 PLAYER3UI_POS = { -550,115,0 };
	const Vector3 PLAYER4UI_POS = { 550,115,0 };
	const Vector3 PLAYER5UI_POS = { -550,-65,0 };
	const Vector3 PLAYER6UI_POS = { 550,-65,0 };
 	const Vector3 PLAYER7UI_POS = { -550,-245,0 };
	const Vector3 PLAYER8UI_POS = { 550,-245,0 };

	const Vector3 PLAYER1STOCK_POS = { -575,208,0 };
	const Vector3 PLAYER2STOCK_POS = { 525, 208, 0 };
	const Vector3 PLAYER3STOCK_POS = { -575,33,0 };
	const Vector3 PLAYER4STOCK_POS = { 525,33,0 };
	const Vector3 PLAYER5STOCK_POS = { -575,-147,0 };
	const Vector3 PLAYER6STOCK_POS = { 525,-147,0 };
	const Vector3 PLAYER7STOCK_POS = { -575,-327,0 };
	const Vector3 PLAYER8STOCK_POS = { 525,-327,0 };

	const Vector3 PLAYER_UI_SIZE = { 0.3f,0.3f,0.3f };
	const Vector3 PLAYER_STOCK_SIZE = { 0.3f,0.3f,0.3f };
	const float STOCKNUM_SIZE = { 0.9 };
	const Vector4 STOCKNUM_COLOR = { 1.0f,1.0f,1.0f,1.0f };
	const Vector2 PL_STOCKNUM_POS[8] = { { -550,230 }, {550,230 }, { -550,55 }, { 550,55 }, { -550,-125 }, { 550,-125 }, { -550,-305 },	{550, -305 } };


}
class UIDisplay : public IGameObject
{
public:
	bool Start();
	void Update();
	~UIDisplay();
	void SetPlayerDeath(int PldeathNum) { m_PlDeath[PldeathNum] = true; };
	void SetPlayerDecStock(int PldecstockNum) { m_PlDecStock[PldecstockNum] = true; };

	void SetPlayerStock(int stock, int plNum);

private:

	std::wstring m_stocknum[10] = { {L"x0"},{L"x1"},{L"x2"},{L"x3"},{L"x4"},{L"x5"}, {L"x6"},{L"x7"},{L"x8"},{L"x9"} };

	SpriteRender* m_playerUI_Sprite[8] = { nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr };

	SpriteRender* m_playerstock_Sprite[8] = { nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr };

	Vector3 m_playerUI_Pos[8] = {
	{ PLAYER1UI_POS },
	{ PLAYER2UI_POS },
	{ PLAYER3UI_POS },
	{ PLAYER4UI_POS },
	{ PLAYER5UI_POS },
	{ PLAYER6UI_POS },
	{ PLAYER7UI_POS },
	{ PLAYER8UI_POS } };
	
	Vector3 m_playerstock_Pos[8] = {
	{ PLAYER1STOCK_POS },
	{ PLAYER2STOCK_POS },
	{ PLAYER3STOCK_POS },
	{ PLAYER4STOCK_POS },
	{ PLAYER5STOCK_POS },
	{ PLAYER6STOCK_POS },
	{ PLAYER7STOCK_POS },
	{ PLAYER8STOCK_POS } };

	FontRender* m_playerstock_FontRender[8] = { nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr };
	
	int loopcount = 0;
	int explosioncount[8] = { 0,0,0,0,0,0,0,0 };
	int changeframenum[4] = { 1, 10 , 20, 40 };
	bool m_PlDecStock[8] = { false,false,false,false,false,false,false,false };
	bool m_PlDeath[8] = { false,false,false,false,false,false,false,false };
};