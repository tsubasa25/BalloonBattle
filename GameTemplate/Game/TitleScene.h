#pragma once
namespace 
{
	Vector4 TITLE_COLOR = { 1,0,0,0 };//タイトルの色
	Vector4 CHOOSING_COLOR = { 0,1,1,0 };//選択中の色
	Vector4 NOTCHOOSING_COLOR = { 1,1,1,0 };//選択されてない時の色


}
class TitleScene : public IGameObject
{
public:
	bool Start();
	void Update();
	~TitleScene();
	

private:
	FontRender* m_title_FontRender = NewGO<FontRender>(0);//タイトルの文字
	std::wstring m_title = L"TITLE";
	FontRender* m_playernumber_FontRender = NewGO<FontRender>(0);//タイトルの文字
	std::wstring m_playernumber = L"プレイ人数";
	FontRender* m_start_FontRender = NewGO<FontRender>(0);//タイトルの文字
	std::wstring m_start = L"はじめる";
	FontRender* m_exit_FontRender = NewGO<FontRender>(0);//タイトルの文字
	std::wstring m_exit = L"おわる";

	FontRender* m_playerCount_FontRender = NewGO<FontRender>(0);//タイトルの文字

	int m_playerCount = 4;
	int m_selectNum = 0;

};

