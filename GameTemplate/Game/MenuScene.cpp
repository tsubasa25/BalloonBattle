#include "stdafx.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "BackGround.h"
#include "UIDisplay.h"

MenuScene::~MenuScene()
{
	DeleteGO(m_plCountFontRender);
	DeleteGO(m_stageSelectFontRender);
}

bool MenuScene::Start()
{
	m_plCountFontRender = NewGO<FontRender>(0);
	m_plCountFontRender->SetText(L"プレイ人数 : " + std::to_wstring(m_playerCount));

	m_stageSelectFontRender = NewGO<FontRender>(0);
	m_stageSelectFontRender->SetPosition({0.0f, -30.0f});
	m_stageSelectFontRender->SetText(L"ステージ : " + std::to_wstring(m_stageNum) + L" SkyIslandStage");

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

void MenuScene::AddSelectNum(int num)
{
	m_selectNum += num;
	//0～1までしか選択できない。
	if (m_selectNum > 1)
		m_selectNum = 1;
	else if (m_selectNum < 0)
		m_selectNum = 0;
}

void MenuScene::SetPlayerCount()
{
	if (g_pad[0]->IsTrigger(enButtonRight))
	{
		AddPlayerCount(1);
		m_plCountFontRender->SetText(L"プレイ人数 : " + std::to_wstring(m_playerCount));
	}
	else if (g_pad[0]->IsTrigger(enButtonLeft))
	{
		AddPlayerCount(-1);
		m_plCountFontRender->SetText(L"プレイ人数 : " + std::to_wstring(m_playerCount));
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
		m_stageSelectFontRender->SetText(L"ステージ : " + std::to_wstring(m_stageNum) + L" SkyIslandStage");
		break;
	case 2:
		m_stageSelectFontRender->SetText(L"ステージ : " + std::to_wstring(m_stageNum) + L" BuildingStage");
		break;
	}
}

//プレイ人数を加える。
void MenuScene::AddStageNum(int num)
{
	m_stageNum += num;
	//1～8人までしか選択できない。
	if (m_stageNum > 2)
		m_stageNum = 2;
	else if (m_stageNum < 1)
		m_stageNum = 1;
}