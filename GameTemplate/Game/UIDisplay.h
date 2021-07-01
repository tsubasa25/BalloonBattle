#pragma once
namespace {
	const Vector3 PLAYER_UI_SIZE = { 0.3f,0.3,0.3f };
	const Vector3 PLAYER_STOCK_SIZE = { 1.0f,1.0f,1.0f };
}
class UIDisplay : public IGameObject
{
public:
	bool Start();
	void Update();
	~UIDisplay();
	
private:
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

	Vector3 m_player1stock_Pos = { -550,290,0 };
	Vector3 m_player2stock_Pos = { 550,290,0 };
	Vector3 m_player3stock_Pos = { -550,115,0 };
	Vector3 m_player4stock_Pos = { 550,115,0 };
	Vector3 m_player5stock_Pos = { -550,-65,0 };
	Vector3 m_player6stock_Pos = { 550,-65,0 };
	Vector3 m_player7stock_Pos = { -550,-245,0 };
	Vector3 m_player8stock_Pos = { 550,-245,0 };
};

