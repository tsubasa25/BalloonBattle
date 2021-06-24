#pragma once
namespace 
{
	Vector4 TITLE_COLOR = { 1,0,0,0 };//�^�C�g���̐F
	Vector4 CHOOSING_COLOR = { 0,1,1,0 };//�I�𒆂̐F
	Vector4 NOTCHOOSING_COLOR = { 1,1,1,0 };//�I������ĂȂ����̐F


}
class TitleScene : public IGameObject
{
public:
	bool Start();
	void Update();
	~TitleScene();
	

private:
	FontRender* m_title_FontRender = NewGO<FontRender>(0);//�^�C�g���̕���
	std::wstring m_title = L"TITLE";
	FontRender* m_playernumber_FontRender = NewGO<FontRender>(0);//�^�C�g���̕���
	std::wstring m_playernumber = L"�v���C�l��";
	FontRender* m_start_FontRender = NewGO<FontRender>(0);//�^�C�g���̕���
	std::wstring m_start = L"�͂��߂�";
	FontRender* m_exit_FontRender = NewGO<FontRender>(0);//�^�C�g���̕���
	std::wstring m_exit = L"�����";

	FontRender* m_playerCount_FontRender = NewGO<FontRender>(0);//�^�C�g���̕���

	int m_playerCount = 4;
	int m_selectNum = 0;

};

