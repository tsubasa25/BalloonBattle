#include "stdafx.h"
#include "TitleScene.h"
#include "BackGround.h"
#include "GameScene.h"
#include "UIDisplay.h"
#include "MenuScene.h"

TitleScene::~TitleScene()
{
	DeleteGO(m_back_Sprite);
	DeleteGO(m_cloud1_Sprite);
	DeleteGO(m_cloud2_Sprite);
	DeleteGO(m_undercloud01_Sprite);
	DeleteGO(m_undercloud02_Sprite);
	DeleteGO(m_undercloud11_Sprite);
	DeleteGO(m_undercloud12_Sprite);
	DeleteGO(m_undercloud21_Sprite);
	DeleteGO(m_undercloud22_Sprite);
	
	DeleteGO(m_title_Sprite);
	DeleteGO(m_start_Sprite);
	DeleteGO(m_option_Sprite);
	DeleteGO(m_exit_Sprite);
	DeleteGO(m_titleBGM);
}
bool TitleScene::Start()
{
	m_back_Sprite = NewGO<SpriteRender>(0);
	m_back_Sprite->Init("Assets/Image/back.dds", 1280, 720);
	
	m_cloud1_Sprite = NewGO<SpriteRender>(0);
	m_cloud1_Sprite->Init("Assets/Image/cloud.dds", 1280, 720);
	m_cloud2_Sprite = NewGO<SpriteRender>(0);
	m_cloud2_Sprite->Init("Assets/Image/cloud.dds", 1280, 720);
	m_cloud2_Sprite->SetPosition({ m_cloud2Pos });

	m_undercloud21_Sprite = NewGO<SpriteRender>(0);
	m_undercloud21_Sprite->Init("Assets/Image/under_cloud2.dds", 1282, 730);
	m_undercloud22_Sprite = NewGO<SpriteRender>(0);
	m_undercloud22_Sprite->Init("Assets/Image/under_cloud2.dds", 1282, 730);
	m_undercloud22_Sprite->SetPosition({ m_undercloud22Pos });
	
	m_undercloud11_Sprite = NewGO<SpriteRender>(0);
	m_undercloud11_Sprite->Init("Assets/Image/under_cloud1.dds", 1282, 740);
	m_undercloud12_Sprite = NewGO<SpriteRender>(0);
	m_undercloud12_Sprite->Init("Assets/Image/under_cloud1.dds", 1282, 740);
	m_undercloud12_Sprite->SetPosition({ m_undercloud12Pos });

	m_undercloud01_Sprite = NewGO<SpriteRender>(0);
	m_undercloud01_Sprite->Init("Assets/Image/under_cloud0.dds", 1282, 750);
	m_undercloud02_Sprite = NewGO<SpriteRender>(0);
	m_undercloud02_Sprite->Init("Assets/Image/under_cloud0.dds", 1282, 750);
	m_undercloud02_Sprite->SetPosition({ m_undercloud02Pos });
	

	m_title_Sprite = NewGO<SpriteRender>(2);
	m_title_Sprite->Init("Assets/Image/titleLogo.dds", 1280, 720);

	m_exit_Sprite = NewGO<SpriteRender>(3);
	m_exit_Sprite->Init("Assets/Image/EXIT.dds", 252, 420);
	m_exit_Sprite->SetScale(BALLOON_SIZE);
	m_exit_Sprite->SetPosition(EXIT_INI_POS);

	m_start_Sprite = NewGO<SpriteRender>(3);
	m_start_Sprite->Init("Assets/Image/START.dds", 252, 420);
	m_start_Sprite->SetScale(BALLOON_SIZE);
	m_start_Sprite->SetPosition(START_INI_POS);

	m_option_Sprite = NewGO<SpriteRender>(3);
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

	BackMove();

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

void TitleScene::BackMove()
{
	if (m_cloud1Pos.x < -1280) {
		m_cloud1Pos.x = 1280;
	}
	if (m_cloud2Pos.x < -1280) {
		m_cloud2Pos.x = 1280;
	}
	if (m_undercloud01Pos.x > 1280) {
		m_undercloud01Pos.x = -1280;
	}
	if (m_undercloud02Pos.x > 1280) {
		m_undercloud02Pos.x = -1280;
	}
	if (m_undercloud11Pos.x > 1280) {
		m_undercloud11Pos.x = -1280;
	}
	if (m_undercloud12Pos.x > 1280) {
		m_undercloud12Pos.x = -1280;
	}
	if (m_undercloud21Pos.x > 1280) {
		m_undercloud21Pos.x = -1280;
	}
	if (m_undercloud22Pos.x > 1280) {
		m_undercloud22Pos.x = -1280;
	}


	m_cloud1Pos.x-= m_BM_MoveSpeed;
	m_cloud2Pos.x-= m_BM_MoveSpeed;
	m_undercloud21Pos.x+=m_BM_MoveSpeed;
	m_undercloud22Pos.x+=m_BM_MoveSpeed;
	m_undercloud11Pos.x+=m_BM_MoveSpeed*2;
	m_undercloud12Pos.x+=m_BM_MoveSpeed*2;
	m_undercloud01Pos.x+=m_BM_MoveSpeed*3;
	m_undercloud02Pos.x+=m_BM_MoveSpeed*3;

	m_cloud1_Sprite->SetPosition({ m_cloud1Pos });
	m_cloud2_Sprite->SetPosition({ m_cloud2Pos });

	m_undercloud21_Sprite->SetPosition({ m_undercloud21Pos });
	m_undercloud22_Sprite->SetPosition({ m_undercloud22Pos });
	m_undercloud11_Sprite->SetPosition({ m_undercloud11Pos });
	m_undercloud12_Sprite->SetPosition({ m_undercloud12Pos });
	m_undercloud01_Sprite->SetPosition({ m_undercloud01Pos });
	m_undercloud02_Sprite->SetPosition({ m_undercloud02Pos });
	

}
