#pragma once
class Player;
class BackGround;
class GameScene;
namespace
{
	const int MODE_GAME_SET = 1;
	const int MODE_ZOOM_WINNER = 2;
	const int MODE_TIME_UP = 3;
	const int MODE_DRAW = 4;
	const int MODE_MENU = 5;

	const Vector2 RESULT_CURSOR_FONT_INI_POS = { -200.0f,30.0f };
	const Vector2 RETRI_FONT_POS = { -150.0f,30.0f };
	const Vector2 BACK_MENU_FONT_POS = { -150.0f,-30.0f };
	const Vector2 BACK_TIRLE_FONT_POS = { -150.0f, -90.0f };
	const float INI_CURSOR_MOVE_SPEED_X = 2.0f;
	const float SOUND_RESULT_SE_VOLUME = 0.6f;
	const float SOUND_RESULT_BGM_VOLUME = 0.3f;
}

class ResultScene : public IGameObject
{
private:
	Player* m_winnerPl = nullptr;
	FontRender* m_gameSetFontRender = nullptr;
	int m_gameSetFontTimer = 100;
	int m_winFontTimer = 200;
	Vector3 m_winnerPos = { Vector3::Zero };

	FontRender* m_winFontRender = nullptr;
	ResultScene* m_resultScene = nullptr;

	int m_mode = 0;
	Vector3 m_cameraPos = { 0.0f, 300.0f, -10000.0f };
	float m_cameraMoveSpeed = 1.0f;

	Vector2 m_cursorPos = { RESULT_CURSOR_FONT_INI_POS };
	float m_cursorMoveSpeedX = INI_CURSOR_MOVE_SPEED_X;
	FontRender* m_cursorFontRender = nullptr;

	FontRender* m_retriFontRender = nullptr;
	FontRender* m_backMenuFontRender = nullptr;
	FontRender* m_backTitleFontRender = nullptr;
	int m_selectMenuNum = 0;

	int m_stageNum = 0;

	BackGround* m_BG= nullptr;
	GameScene* m_gameScene = nullptr;
	SoundSource* m_resultBGM = nullptr;
	SoundSource* m_resultSE = nullptr;

	Vector2 plFontPos = {-320.0f, 50.0f};

	bool m_lookStageFlag = false;
	bool m_resultBGMFlg = false;

public:
	~ResultScene();
	bool Start();
	void Update();

	void SetWinner(Player* Pl) { m_winnerPl = Pl; }

	void GameSet();
	void ZoomWinner();
	void TimeUp();
	void Draw();
	void Menu();

	void SetCursorPos();
	void AddSelectMenuNum(int num);

	void SetStageNum(int num) { m_stageNum = num; };

	void SetResultMode(int mode) { m_mode = mode; };
};

