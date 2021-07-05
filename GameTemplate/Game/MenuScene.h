#pragma once
class BackGround;

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
	FontRender* m_plCountFontRender = nullptr;
	FontRender* m_stageSelectFontRender = nullptr;
	int m_selectNum = 0;
	int m_stageNum = 1;
	BackGround* m_backGround = nullptr;
};

