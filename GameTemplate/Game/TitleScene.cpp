#include "stdafx.h"
#include "TitleScene.h"
#include "BackGround.h"
#include "GameScene.h"
TitleScene::~TitleScene()
{
	DeleteGO(m_title_FontRender);
	DeleteGO(m_playernumber_FontRender);
	DeleteGO(m_exit_FontRender);
	DeleteGO(m_playerCount_FontRender);
}
bool TitleScene::Start()
{	
	m_title_FontRender->SetText(m_title);
	m_title_FontRender->SetColor(TITLE_COLOR);
	m_title_FontRender->SetPosition({ -100,200 });
	m_title_FontRender->SetScale({ 2 });

	m_start_FontRender->SetText(m_start);
	m_start_FontRender->SetColor(NOTCHOOSING_COLOR);
	m_start_FontRender->SetPosition({ -100,0 });
	m_start_FontRender->SetScale({ 1 });

	m_playernumber_FontRender->SetText(m_playernumber);
	m_playernumber_FontRender->SetColor(NOTCHOOSING_COLOR);
	m_playernumber_FontRender->SetPosition({ -100,-100});
	m_playernumber_FontRender->SetScale({ 1 });

	m_playerCount_FontRender->SetText(std::to_wstring(m_playerCount));
	m_playerCount_FontRender->SetColor(NOTCHOOSING_COLOR);
	m_playerCount_FontRender->SetPosition({ 200,-100 });
	m_playerCount_FontRender->SetScale({ 1 });

	m_exit_FontRender->SetText(m_exit);
	m_exit_FontRender->SetColor(NOTCHOOSING_COLOR);
	m_exit_FontRender->SetPosition({ -100,-200 });
	m_exit_FontRender->SetScale({ 1 });
	return true;
}
	
void TitleScene::Update()
{
	if (g_pad[0]->IsTrigger(enButtonUp)){
		m_selectNum -= 1;
	}
	if (g_pad[0]->IsTrigger(enButtonDown)) {
		m_selectNum += 1;
	}
	if (m_selectNum > 2) {
		m_selectNum = 0;
	}
	if (m_selectNum < 0) {
		m_selectNum = 2;
	}

	switch (m_selectNum) {
	case 0:
		m_start_FontRender->SetColor(CHOOSING_COLOR);
		m_playernumber_FontRender->SetColor(NOTCHOOSING_COLOR);
		m_exit_FontRender->SetColor(NOTCHOOSING_COLOR);
		break;

	case 1:
		m_start_FontRender->SetColor(NOTCHOOSING_COLOR);
		m_playernumber_FontRender->SetColor(CHOOSING_COLOR);
		m_exit_FontRender->SetColor(NOTCHOOSING_COLOR);
		break;

	case 2:
		m_start_FontRender->SetColor(NOTCHOOSING_COLOR);
		m_playernumber_FontRender->SetColor(NOTCHOOSING_COLOR);
		m_exit_FontRender->SetColor(CHOOSING_COLOR);
		break;

	default:
		break;
	}

	if (m_selectNum == 0 && g_pad[0]->IsTrigger(enButtonA)) {
		GameScene* gameScene = NewGO<GameScene>(0, "gameScene");
		gameScene->SetPlayerCount(m_playerCount);
		NewGO<BackGround>(0);
		DeleteGO(this);
	}

	if (m_selectNum == 1 && g_pad[0]->IsTrigger(enButtonRight)){
		m_playerCount += 1;
		if (m_playerCount > 8) {
			m_playerCount = 8;
		}
		m_playerCount_FontRender->SetText(std::to_wstring(m_playerCount));
	}
	if (m_selectNum == 1 && g_pad[0]->IsTrigger(enButtonLeft)) {
		m_playerCount -= 1;
		if (m_playerCount < 0) {
			m_playerCount = 0;
		}
		m_playerCount_FontRender->SetText(std::to_wstring(m_playerCount));
	}

}
