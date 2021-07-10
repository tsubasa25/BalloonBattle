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
	m_plCountFontRender->SetText(L"�v���C�l�� : " + std::to_wstring(m_playerCount) + L"�l");

	m_stageSelectFontRender = NewGO<FontRender>(0);
	m_stageSelectFontRender->SetPosition(STAGE_NUM_FONT_POS);
	m_stageSelectFontRender->SetText(L"�X�e�[�W  : " + std::to_wstring(m_stageNum) + L" SkyIslandStage");

	m_menuBGM = NewGO<SoundSource>(0);
	m_menuBGM->Init(L"Assets/sound/�}�b�v�I�����BGM.wav", SoundType::enBGM);
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

//�J�[�\���̈ʒu�����߂�B
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

//�J�[�\���̈ʒu�����炷�B
void MenuScene::AddSelectNum(int num)
{
	m_selectNum += num;
	//0�`1�܂ł����I���ł��Ȃ��B
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

//�v���C�l����I������B
void MenuScene::SetPlayerCount()
{
	if (g_pad[0]->IsTrigger(enButtonRight))
	{
		AddPlayerCount(1);
		m_plCountFontRender->SetText(L"�v���C�l�� : " + std::to_wstring(m_playerCount) + L"�l");
	}
	else if (g_pad[0]->IsTrigger(enButtonLeft))
	{
		AddPlayerCount(-1);
		m_plCountFontRender->SetText(L"�v���C�l�� : " + std::to_wstring(m_playerCount) + L"�l");
	}
}

//�v���C�l����������B
void MenuScene::AddPlayerCount(int num)
{
	m_playerCount += num;
	//1�`8�l�܂ł����I���ł��Ȃ��B
	if (m_playerCount > 8)
		m_playerCount = 8;
	else if (m_playerCount < 1)
		m_playerCount = 1;
}

//�X�e�[�W��I������
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

	//�X�e�[�W����\��
	switch (m_stageNum)
	{
	case 1:
		m_stageSelectFontRender->SetText(L"�X�e�[�W  : " + std::to_wstring(m_stageNum) + L" SkyIslandStage");
		break;
	case 2:
		m_stageSelectFontRender->SetText(L"�X�e�[�W  : " + std::to_wstring(m_stageNum) + L" BuildingStage");
		break;
	case 3:
		m_stageSelectFontRender->SetText(L"�X�e�[�W  : " + std::to_wstring(m_stageNum) + L" TrapStage");
		break;
	}
}

//�X�e�[�W�̔ԍ���ύX����B
void MenuScene::AddStageNum(int num)
{
	m_stageNum += num;
	//1�`3�܂ł����I���ł��Ȃ��B
	if (m_stageNum > 3)
		m_stageNum = 3;
	else if (m_stageNum < 1)
		m_stageNum = 1;
}
