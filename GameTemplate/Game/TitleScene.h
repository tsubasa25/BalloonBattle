#pragma once
namespace 
{
	const Vector4 TITLE_COLOR = { 1,0,0,0 };//タイトルの色
	const Vector4 CHOOSING_COLOR = { 0,1,1,0 };//選択中の色
	const Vector4 NOTCHOOSING_COLOR = { 1,1,1,0 };//選択されてない時の色
	const Vector2 SPRITE_TITLE_POSITION = { -250,200 };//タイトルの位置
	const Vector2 SPRITE_START_POSITION = { -85,0 };//スタートボタンの位置
	const Vector2 SPRITE_PLAYERNUM_POSITION = { -100,-100 };//プレイヤー人数設定ボタンの位置
	const Vector2 SPRITE_PLAYERCOUNT_POSITION = { 200,-100 };//プレイヤー人数の位置
	const Vector2 SPRITE_EXIT_POSITION = { -70,-200 };//ゲーム終了ボタンの位置
	const int SPRITE_TITLE_SCALE = 2;//タイトルの大きさ
	const int SPRITE_START_SCALE = 1;//スタートボタンの大きさ
	const int SPRITE_PLAYERNUM_SCALE = 1;//プレイヤー人数設定ボタンの大きさ
	const int SPRITE_PLAYERCOUNT_SCALE = 1;//プレイヤー人数の大きさ
	const int SPRITE_EXIT_SCALE = 1;//ゲーム終了ボタンの大きさ
	const int MIN_PLAYERCOUNT = 1;//最低プレイヤー人数
	const int MAX_PLAYERCOUNT = 8;//最大プレイヤー人数
}
class TitleScene : public IGameObject
{
public:
	bool Start();
	void Update();
	~TitleScene();

private:
	FontRender* m_title_FontRender = NewGO<FontRender>(0);//タイトルの文字
	std::wstring m_title = L"BALLOON BATTLE";
	FontRender* m_playernumber_FontRender = NewGO<FontRender>(0);//タイトルの文字
	std::wstring m_playernumber = L"PLAYER";
	FontRender* m_start_FontRender = NewGO<FontRender>(0);//タイトルの文字
	std::wstring m_start = L"START";
	FontRender* m_exit_FontRender = NewGO<FontRender>(0);//タイトルの文字
	std::wstring m_exit = L"EXIT";

	FontRender* m_playerCount_FontRender = NewGO<FontRender>(0);//タイトルの文字

	int m_playerCount = 4;
	int m_selectNum = 0;

};

