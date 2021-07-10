#pragma once
class BackGround;

namespace
{
	const Vector2 CURSOR_FONT_INI_POS = { -350.0f,30.0f };	//ステージ選択のテキストの位置
	const Vector2 PLYAER_COUNT_FONT_POS = { -300.0f,30.0f };	//プレイ人数のテキストの位置
	const Vector2 STAGE_NUM_FONT_POS = { -300.0f,-30.0f };	//ステージ選択のテキストの位置
	const float SOUND_MENU_BGM_VOLUME = 0.2f;
}

class MenuScene : public IGameObject
{
public:
	~MenuScene();
	bool Start();
	void Update();

	void SetSelectNum();
	void AddSelectNum(int num);

	void SetPlayerCount();
	void AddPlayerCount(int num);

	void SetStage();
	void AddStageNum(int num);

private:
	int m_playerCount = 1;
	FontRender* m_cursorFontRender = nullptr;
	FontRender* m_plCountFontRender = nullptr;
	FontRender* m_stageSelectFontRender = nullptr;
	int m_selectNum = 0;
	int m_stageNum = 1;

	Vector2 m_cursorPos = { CURSOR_FONT_INI_POS };

	BackGround* m_backGround = nullptr;

	SoundSource* m_menuBGM = nullptr;
};

