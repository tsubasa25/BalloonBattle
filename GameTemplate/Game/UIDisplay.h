#pragma once
namespace {
	const Vector3 PLAYER1UI_POS = { -575,208,0 };
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

private:

	std::wstring m_stocknum[6] = { {L"x0"},{L"x1"},{L"x2"},{L"x3"},{L"x4"},{L"x5"} };

	SpriteRender* m_playerUI_Sprite[8] = { nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr };

	SpriteRender* m_playerstock_Sprite[8] = { nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr };

	Vector3 m_playerUI_Pos[8] = {
	{ -550, 290, 0 },
	{ 550,290,0 },
	{ -550,115,0 },
	{ 550,115,0 },
	{ -550,-65,0 },
	{ 550,-65,0 },
	{ -550,-245,0 },
	{ 550,-245,0 } };
	
	Vector3 m_playerstock_Pos[8] ={
	{ PLAYER1UI_POS },
	{ 525, 208, 0 },
	{ -575,33,0 },
	{ 525,33,0 },
	{ -575,-147,0 },
	{ 525,-147,0 },
	{ -575,-327,0 },
	{ 525,-327,0 }	};

	FontRender* m_playerstock_FontRender[8] = { nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr };
	
	int loopcount = 0;
	int explosioncount[8] = { 0,0,0,0,0,0,0,0 };
	int changeframenum[4] = { 1, 10 , 20, 40 };
	bool m_PlDecStock[8] = { false,false,false,false,false,false,false,false };
	bool m_PlDeath[8] = { false,false,false,false,false,false,false,false };
};