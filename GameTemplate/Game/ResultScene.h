#pragma once
class Player;
class BackGround;
class GameScene;
namespace
{
	const Vector3 RESULT_CURSOR_FONT_INI_POS = { -250.0f,-50.0f, 0.0f };
	const Vector3 CAMERA_INI_POS = { 0.0f, 300.0f, -10000.0f };
	const Vector2 WINNER_FONT_POS = { -320.0f, 50.0f };
	const Vector2 RETRI_FONT_POS = { -150.0f,30.0f };
	const Vector2 BACK_MENU_FONT_POS = { -150.0f,-30.0f };
	const Vector2 BACK_TITLE_FONT_POS = { -150.0f, -90.0f };
	const float INI_CURSOR_MOVE_SPEED_X = 0.0f;
	const float CURSOR_FONT_MAX_POS_X = -200;
	const float SOUND_RESULT_SE_VOLUME = 0.6f;
	const float SOUND_RESULT_BGM_VOLUME = 0.3f;
	const int DISPLAYED_FONT_GAMESET_TIME = 100;
	const int DISPLAYED_FONT_WIN_TIME = 220;
}

class ResultScene : public IGameObject
{
private:
	/// <summary>
	/// 勝者のプレイヤー情報
	/// </summary>
	Player* m_winnerPl = nullptr;
	/// <summary>
	/// ”ゲームセット”と表示させる
	/// </summary>
	FontRender* m_gameSetFontRender = nullptr;
	/// <summary>
	/// フォントが表示されている時間
	/// </summary>
	int m_gameSetDisplayedTime = DISPLAYED_FONT_GAMESET_TIME;
	int m_winDisplayedTime = DISPLAYED_FONT_WIN_TIME;
	int m_timeUpDisplayedTime= DISPLAYED_FONT_GAMESET_TIME;
	int m_drawDisplayedTime = DISPLAYED_FONT_WIN_TIME;	
	/// <summary>
	/// 勝者が立つ位置
	/// </summary>
	Vector3 m_winnerPos = { Vector3::Zero };
	/// <summary>
	/// 勝者の番号を表示させる
	/// </summary>
	FontRender* m_winFontRender = nullptr;
	/// <summary>
	/// カメラの位置
	/// </summary>
	Vector3 m_cameraPos = { CAMERA_INI_POS };
	/// <summary>
	/// カメラの移動スピード
	/// </summary>
	float m_cameraMoveSpeed = 1.0f;
	/// <summary>
	/// カーソルの位置
	/// </summary>
	Vector3 m_cursorPos = { RESULT_CURSOR_FONT_INI_POS };
	/// <summary>
	/// カーソルの左右移動のスピード
	/// </summary>
	float m_cursorMoveSpeedX = INI_CURSOR_MOVE_SPEED_X;
	/// <summary>
	/// カーソル画像
	/// </summary>
	SpriteRender* m_cursorSprite = nullptr;
	/// <summary>
	/// "リトライ"
	/// </summary>
	FontRender* m_retriFontRender = nullptr;
	/// <summary>
	/// "メニューへ"
	/// </summary>
	FontRender* m_backMenuFontRender = nullptr;
	/// <summary>
	/// "タイトルへ"
	/// </summary>
	FontRender* m_backTitleFontRender = nullptr;
	
	enum isSelectMenu
	{
		enRetri,
		enBackMenu,
		enBackTitle
	};
	isSelectMenu m_selectMenu = enBackMenu;

	int m_stageNum = 0;

	BackGround* m_BG= nullptr;
	GameScene* m_gameScene = nullptr;
	SoundSource* m_resultBGM = nullptr;
	SoundSource* m_resultSE = nullptr;

	Vector2 m_plFontPos = { WINNER_FONT_POS };

	bool m_lookStageFlag = false;
	bool m_resultBGMFlg = false;

	enum ResultState
	{
		enGameSet,	
		enZoomWinner,
		enTimeUp,
		enDraw,
		enMenu
	};
	ResultState m_resultState = enGameSet;
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
	void isSelectMenu(bool isUp);
	
	void SetStageNum(int num) { m_stageNum = num; };

	void SetResultMode(ResultState state) { m_resultState = state; };
	ResultState GetEnGameSet() { return ResultState::enGameSet; }
	ResultState GetEnTimeUp() { return ResultState::enTimeUp; }

	void EraseUnused();
};

