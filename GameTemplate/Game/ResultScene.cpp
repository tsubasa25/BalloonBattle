#include "stdafx.h"
#include "ResultScene.h"
#include "Player.h"
#include "TitleScene.h"
#include "UIDisplay.h"
#include "GameScene.h"
#include "BackGround.h"

ResultScene::~ResultScene()
{
	DeleteGO(m_selectTitleFontRender);
	QueryGOs<BackGround>("backGround", [this](BackGround* backGround)->bool {
		DeleteGO(backGround);
		return true;
		});
	QueryGOs<GameScene>("gameScene", [this](GameScene* gameScene)->bool {
		DeleteGO(gameScene);
		return true;
		});
}

bool ResultScene::Start()
{
	m_gameSetFontRender = NewGO<FontRender>(0);
	m_gameSetFontRender->SetScale(2.0f);
	m_gameSetFontRender->SetText(L"GAME SET");

	m_mode = MODE_GAME_SET;

	return true;
}
void ResultScene::Update()
{
	switch (m_mode)
	{
	case MODE_GAME_SET:
		GameSet();
		break;
		
	case MODE_ZOOM_WINNER:
		ZoomWinner();
		break;
	case MODE_MENU:
		Menu();
		break;
	}
}

void ResultScene::GameSet()
{
	if (m_gameSetFontTimer > 0)
	{
		m_gameSetFontTimer--;
		return;
	}
	else
	{
		m_mode = MODE_ZOOM_WINNER;
		DeleteGO(m_gameSetFontRender);
		m_winFontRender = NewGO<FontRender>(0);
		m_winFontRender->SetScale(2.0f);
		m_winFontRender->SetText(L"PLAYER " + std::to_wstring(m_winnerPl->GetPlayerNum() + 1) + L"  WIN!!");
		m_winnerPl->SetPosition(m_winnerPos);
		QueryGOs<UIDisplay>("UIdisplay", [this](UIDisplay* UIdisplay)->bool {
			DeleteGO(UIdisplay);
			return true;
			});
	}
}

void ResultScene::ZoomWinner()
{
	if (m_winFontTimer > 0)
	{
		m_winFontTimer--;
		return;
	}
	else if (g_pad[0]->IsTrigger(enButtonA))
	{
		m_mode = MODE_MENU;
		DeleteGO(m_winFontRender);
		m_selectTitleFontRender = NewGO<FontRender>(0);
		m_selectTitleFontRender->SetText(L"A ƒ^ƒCƒgƒ‹‚Ö–ß‚é");
		m_selectTitleFontRender->SetPosition({0.0f, -50.0f});
	}
}

void ResultScene::Menu()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{	
		DeleteGO(m_winnerPl);
		
		DeleteGO(this);
		NewGO<TitleScene>(0, "titleScene");
	}
}