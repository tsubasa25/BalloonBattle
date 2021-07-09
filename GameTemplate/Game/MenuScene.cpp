#include "stdafx.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "BackGround.h"
#include "UIDisplay.h"

MenuScene::~MenuScene()
{
	DeleteGO(m_plCountFontRender);
	DeleteGO(m_stageSelectFontRender);
	DeleteGO(m_cursorFontRender);
	DeleteGO(m_menuBGM);
}

bool MenuScene::Start()
{
	m_cursorFontRender = NewGO<FontRender>(0);
	m_cursorFontRender->SetPosition(m_cursorPos);
	m_cursorFontRender->SetText(L"->");
	
	m_plCountFontRender = NewGO<FontRender>(0);
	m_plCountFontRender->SetPosition(PLYAER_COUNT_FONT_POS);
	m_plCountFontRender->SetText(L"プレイ人数 : " + std::to_wstring(m_playerCount) + L"人");

	m_stageSelectFontRender = NewGO<FontRender>(0);
	m_stageSelectFontRender->SetPosition(STAGE_NUM_FONT_POS);
	m_stageSelectFontRender->SetText(L"ステージ  : " + std::to_wstring(m_stageNum) + L" SkyIslandStage");

	m_menuBGM = NewGO<SoundSource>(0);
	m_menuBGM->Init(L"Assets/sound/マップ選択画面BGM.wav", SoundType::enBGM);
	m_menuBGM->SetVolume(SOUND_MENU_BGM_VOLUME);
	m_menuBGM->Play(true);

	return true;
}
void MenuScene::Update()
{
	SetSelectNum();

	switch (m_selectNum)
	{
	case 0:
		SetPlayerCount();
		break;
	case 1:
		SetStage();
		break;
	}
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		GameScene* gameScene = NewGO<GameScene>(0, "gameScene");
		gameScene->SetPlayerCount(m_playerCount);
		m_backGround = NewGO<BackGround>(0, "backGround");
		m_backGround->SetStageNum(m_stageNum);
		NewGO<UIDisplay>(0, "UIdisplay");//= UIDisplay* UIdisplay 
		DeleteGO(this);
	}
}

//カーソルの位置を決める。
void MenuScene::SetSelectNum()
{
	if (g_pad[0]->IsTrigger(enButtonDown))
	{
		AddSelectNum(1);
	}
	else if (g_pad[0]->IsTrigger(enButtonUp))
	{
		AddSelectNum(-1);
	}
}

//カーソルの位置をずらす。
void MenuScene::AddSelectNum(int num)
{
	m_selectNum += num;
	//0～1までしか選択できない。
	if (m_selectNum > 1)
		m_selectNum = 1;
	else if (m_selectNum < 0)
		m_selectNum = 0;

	switch (m_selectNum)
	{
	case 0:
		m_cursorPos.y = PLYAER_COUNT_FONT_POS.y;
		break;
	case 1:
		m_cursorPos.y = STAGE_NUM_FONT_POS.y;
		break;
	}
	m_cursorFontRender->SetPosition(m_cursorPos);
}

//プレイ人数を選択する。
void MenuScene::SetPlayerCount()
{
	if (g_pad[0]->IsTrigger(enButtonRight))
	{
		AddPlayerCount(1);
		m_plCountFontRender->SetText(L"プレイ人数 : " + std::to_wstring(m_playerCount) + L"人");
	}
	else if (g_pad[0]->IsTrigger(enButtonLeft))
	{
		AddPlayerCount(-1);
		m_plCountFontRender->SetText(L"プレイ人数 : " + std::to_wstring(m_playerCount) + L"人");
	}
}

//プレイ人数を加える。
void MenuScene::AddPlayerCount(int num)
{
	m_playerCount += num;
	//1～8人までしか選択できない。
	if (m_playerCount > 8)
		m_playerCount = 8;
	else if (m_playerCount < 1)
		m_playerCount = 1;
}

//ステージを選択する
void MenuScene::SetStage()
{
	if (g_pad[0]->IsTrigger(enButtonRight))
	{
		AddStageNum(1);
	}
	else if (g_pad[0]->IsTrigger(enButtonLeft))
	{
		AddStageNum(-1);
	}

	//ステージ名を表示
	switch (m_stageNum)
	{
	case 1:
		m_stageSelectFontRender->SetText(L"ステージ  : " + std::to_wstring(m_stageNum) + L" SkyIslandStage");
		break;
	case 2:
		m_stageSelectFontRender->SetText(L"ステージ  : " + std::to_wstring(m_stageNum) + L" BuildingStage");
		break;
	case 3:
		m_stageSelectFontRender->SetText(L"ステージ  : " + std::to_wstring(m_stageNum) + L" TrapStage");
		break;
	}
}

//ステージの番号を変更する。
void MenuScene::AddStageNum(int num)
{
	m_stageNum += num;
	//1～3までしか選択できない。
	if (m_stageNum > 3)
		m_stageNum = 3;
	else if (m_stageNum < 1)
		m_stageNum = 1;
}
