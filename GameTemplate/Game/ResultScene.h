#pragma once
class Player;
namespace
{
	const int MODE_GAME_SET = 1;
	const int MODE_ZOOM_WINNER = 2;
	const int MODE_MENU = 3;
}

class ResultScene : public IGameObject
{
private:
	Player* m_winnerPl = nullptr;
	FontRender* m_gameSetFontRender = nullptr;
	int m_gameSetFontTimer = 200;
	int m_winFontTimer = 500;
	Vector3 m_winnerPos = { Vector3::Zero };

	FontRender* m_winFontRender = nullptr;
	ResultScene* m_resultScene = nullptr;

	FontRender* m_selectTitleFontRender = nullptr;

	int m_mode = 0;

public:
	~ResultScene();
	bool Start();
	void Update();

	void SetWinner(Player* Pl) { m_winnerPl = Pl; }

	void GameSet();
	void ZoomWinner();
	void Menu();
};

