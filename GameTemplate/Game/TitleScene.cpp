#include "stdafx.h"
#include "TitleScene.h"
#include "BackGround.h"
#include "GameScene.h"
#include "UIDisplay.h"
#include "MenuScene.h"

TitleScene::~TitleScene()
{
	DeleteGO(m_title_Sprite);
	DeleteGO(m_start_Sprite);
	DeleteGO(m_option_Sprite);
	DeleteGO(m_exit_Sprite);
	DeleteGO(m_titleBGM);
}
bool TitleScene::Start()
{
	m_title_Sprite = NewGO<SpriteRender>(0);
	m_title_Sprite->Init("Assets/Image/TITLE01.dds", 1280, 720);

	m_exit_Sprite = NewGO<SpriteRender>(1);
	m_exit_Sprite->Init("Assets/Image/EXIT.dds", 252, 420);
	m_exit_Sprite->SetScale(BALLOON_SIZE);
	m_exit_Sprite->SetPosition(EXIT_INI_POS);

	m_start_Sprite = NewGO<SpriteRender>(1);
	m_start_Sprite->Init("Assets/Image/START.dds", 252, 420);
	m_start_Sprite->SetScale(BALLOON_SIZE);
	m_start_Sprite->SetPosition(START_INI_POS);

	m_option_Sprite = NewGO<SpriteRender>(1);
	m_option_Sprite->Init("Assets/Image/OPTION.dds", 252, 420);
	m_option_Sprite->SetScale(BALLOON_SIZE);
	m_option_Sprite->SetPosition(OPTION_INI_POS);

	//BGMを再生
	m_titleBGM = NewGO<SoundSource>(0);
	m_titleBGM->Init(L"Assets/sound/タイトルBGM.wav", SoundType::enBGM);
	m_titleBGM->SetVolume(SOUND_BGM_TITLE_VOLUME);
	m_titleBGM->Play(true);

	return true;
}

void TitleScene::Update()
{
	if (g_pad[0]->IsTrigger(enButtonRight)) {
		m_selectNum += 1;
		m_selectLoopCount = 0;
	}
	if (g_pad[0]->IsTrigger(enButtonLeft)) {
		m_selectNum -= 1;
		m_selectLoopCount = 0;
	}
	if (m_selectNum > 2) {
		m_selectNum = 0;
	}
	if (m_selectNum < 0) {
		m_selectNum = 2;
	}

	switch (m_selectNum) {
	case 0:
		m_selectLoopCount += 0.05f;
		m_exitPos.y = BALLOON_INI_POSY + (sin(m_selectLoopCount)) * 40.0f;
		m_startPos.y = BALLOON_INI_POSY;
		m_optionPos.y = BALLOON_INI_POSY;
		break;

	case 1:
		m_selectLoopCount += 0.05f;
		m_startPos.y = BALLOON_INI_POSY + (sin(m_selectLoopCount)) * 40.0f;
		m_exitPos.y = BALLOON_INI_POSY;
		m_optionPos.y = BALLOON_INI_POSY;
		break;

	case 2:
		m_selectLoopCount += 0.05f;
		m_optionPos.y = BALLOON_INI_POSY + (sin(m_selectLoopCount)) * 40.0f;
		m_exitPos.y = BALLOON_INI_POSY;
		m_startPos.y = BALLOON_INI_POSY;
		break;

	default:
		break;
	}

	if (FloatingFlg == true) {
		FloatingFlg = false;
		ss = NewGO<SoundSource>(0);
		ss->Init(L"Assets/sound/風船の浮遊する音.wav");
		ss->SetVolume(0.2);
		ss->Play(true);
	}

	if (g_pad[0]->IsTrigger(enButtonRight) || g_pad[0]->IsTrigger(enButtonLeft)) {

		if (FloatingFlg == false) {
			DeleteGO(ss);
			FloatingFlg = true;
		}
		SoundSource* ss = NewGO<SoundSource>(0);
		ss->Init(L"Assets/sound/選択音.wav");
		ss->Play(false);
	}

	if (m_selectNum == 1 && g_pad[0]->IsTrigger(enButtonA)) {
		DeleteGO(ss);
		SoundSource* ss = NewGO<SoundSource>(0);
		ss->Init(L"Assets/sound/決定音.wav");
		ss->Play(false);
		NewGO<MenuScene>(0, "menuScene");
		DeleteGO(this);
	}
	m_option_Sprite->SetPosition(m_optionPos);
	m_start_Sprite->SetPosition(m_startPos);
	m_exit_Sprite->SetPosition(m_exitPos);
}
