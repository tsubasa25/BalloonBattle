#include "stdafx.h"
#include "ResultScene.h"
#include "Player.h"
#include "TitleScene.h"
#include "UIDisplay.h"
#include "GameScene.h"
#include "BackGround.h"
#include "GimmickNeedle.h"
#include "MenuScene.h"

ResultScene::~ResultScene()
{
	DeleteGO(m_retriFontRender);
	DeleteGO(m_backMenuFontRender);
	DeleteGO(m_backTitleFontRender);
	DeleteGO(m_cursorFontRender);
}

bool ResultScene::Start()
{
	m_BG = FindGO<BackGround>("backGround");
	m_gameScene = FindGO<GameScene>("gameScene");

	m_gameSetFontRender = NewGO<FontRender>(0);
	m_gameSetFontRender->SetPosition({-200.0f,0.0f});
	m_gameSetFontRender->SetScale(2.0f);
	m_gameSetFontRender->SetText(L"GAME SET");
	m_gameSetFontRender->SetShadowFlag(true);
	m_gameSetFontRender->SetShadowColor({0.0f,0.0f,0.0f,1.0f});

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
		m_winFontRender->SetText(L"PLAYER " + std::to_wstring(m_winnerPl->GetPlayerNum() + 1) + L" WIN!!");
		m_winFontRender->SetPosition({ -300.0f,0.0f });
		m_winFontRender->SetShadowFlag(true);
		m_winFontRender->SetShadowColor({ 0.0f,0.0f,0.0f,1.0f });

		m_winnerPl->SetPosition(m_winnerPos);
		QueryGOs<UIDisplay>("UIdisplay", [this](UIDisplay* UIdisplay)->bool {
			DeleteGO(UIdisplay);
			return true;
			});
		QueryGOs<WindTurbine>("windTurbine", [this](WindTurbine* windTurbine)->bool {
			DeleteGO(windTurbine);
			return true;
			});
		QueryGOs<GimmickNeedle>("gimmickNeedle", [this](GimmickNeedle* gimmickNeedle)->bool {
			DeleteGO(gimmickNeedle);
			return true;
			});

		g_camera3D->SetPosition(m_cameraPos);
		g_camera3D->SetTarget({0.0f,50.0f, 0.0f});
	}
}

void ResultScene::ZoomWinner()
{
	if (m_winFontTimer > 0)
	{
		m_winFontTimer--;
		m_cameraMoveSpeed = m_cameraMoveSpeed * 1.05f;
		m_cameraPos.z += m_cameraMoveSpeed;
		if (m_cameraPos.z > -200.0f)
		{
			m_cameraPos.z = -200.0f;
		}
		g_camera3D->SetPosition(m_cameraPos);
		return;
	}
	else if (g_pad[0]->IsTrigger(enButtonA))
	{
		m_mode = MODE_MENU;
		DeleteGO(m_winFontRender);

		m_cursorFontRender = NewGO<FontRender>(1);
		m_cursorFontRender->SetPosition(m_cursorPos);
		m_cursorFontRender->SetText(L"->");
		m_cursorFontRender->SetShadowFlag(true);
		m_cursorFontRender->SetShadowColor({0.0f,0.0f,0.0f,1.0f});

		m_retriFontRender = NewGO<FontRender>(1);
		m_retriFontRender->SetPosition(RETRI_FONT_POS);
		m_retriFontRender->SetText(L"もう一度遊ぶ。");
		m_retriFontRender->SetShadowFlag(true);
		m_retriFontRender->SetShadowColor({ 0.0f,0.0f,0.0f,1.0f });

		m_backMenuFontRender = NewGO<FontRender>(1);
		m_backMenuFontRender->SetPosition(BACK_MENU_FONT_POS);
		m_backMenuFontRender->SetText(L"メニューへ戻る。");
		m_backMenuFontRender->SetShadowFlag(true);
		m_backMenuFontRender->SetShadowColor({ 0.0f,0.0f,0.0f,1.0f });

		m_backTitleFontRender = NewGO<FontRender>(1);
		m_backTitleFontRender->SetPosition(BACK_TIRLE_FONT_POS);
		m_backTitleFontRender->SetText(L"タイトルへ戻る。");
		m_backTitleFontRender->SetShadowFlag(true);
		m_backTitleFontRender->SetShadowColor({ 0.0f,0.0f,0.0f,1.0f });

	
	}
}

void ResultScene::Menu()
{
	SetCursorPos();

	if (g_pad[0]->IsTrigger(enButtonA))
	{	
		if (m_selectMenuNum == 0)
		{
			DeleteGO(m_winnerPl);
			
			m_gameScene->Retri();
			m_gameScene->SetGameState(1);
			m_stageNum = m_BG->GetStageNum();
			m_BG->Retri();
			DeleteGO(m_BG);
				
			BackGround* backGround = NewGO<BackGround>(0, "backGround");
			backGround->SetStageNum(m_stageNum);
			NewGO<UIDisplay>(0, "UIdisplay");
			DeleteGO(this);
		}
		else if (m_selectMenuNum == 1)
		{
			DeleteGO(m_gameScene);
			
			DeleteGO(m_BG);
				
			DeleteGO(m_winnerPl);
			DeleteGO(this);
			NewGO<MenuScene>(0, "menuScene");
		}
		else if (m_selectMenuNum == 2)
		{
				DeleteGO(m_gameScene);

			DeleteGO(m_BG);
				
			DeleteGO(m_winnerPl);
			DeleteGO(this);
			NewGO<TitleScene>(0, "titleScene");
		}
	}
}
//カーソルの位置を決める。
void ResultScene::SetCursorPos()
{
	if (g_pad[0]->IsTrigger(enButtonDown))
	{
		AddSelectMenuNum(1);
	}
	else if (g_pad[0]->IsTrigger(enButtonUp))
	{
		AddSelectMenuNum(-1);
	}
}

//カーソルの位置をずらす。
void ResultScene::AddSelectMenuNum(int num)
{
	m_selectMenuNum += num;
	//0～2までしか選択できない。
	if (m_selectMenuNum > 2)
		m_selectMenuNum = 2;
	else if (m_selectMenuNum < 0)
		m_selectMenuNum = 0;

	switch (m_selectMenuNum)
	{
	case 0:
		m_cursorPos.y = RETRI_FONT_POS.y;
		break;
	case 1:
		m_cursorPos.y = BACK_MENU_FONT_POS.y;
		break;
	case 2:
		m_cursorPos.y = BACK_TIRLE_FONT_POS.y;
		break;
	}
	m_cursorFontRender->SetPosition(m_cursorPos);
}