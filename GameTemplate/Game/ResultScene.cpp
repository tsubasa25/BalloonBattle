#include "stdafx.h"
#include "ResultScene.h"
#include "Player.h"
#include "TitleScene.h"
#include "UIDisplay.h"
#include "GameScene.h"
#include "BackGround.h"
#include "GimmickNeedle.h"
#include "SelectScene.h"
#include "TitleBack.h"
#include "GameTimer.h"
#include "BalloonAir.h"

namespace
{
	const Vector3 CAMERA_TARGET_POSITION = { 0.0f,100.0f, 0.0f };
	const Vector2 GAMESET_FONT_POSITION = { -200.0f,0.0f };
	const Vector2 WIN_FONT_POSITION = { -300.0f,0.0f };
	const Vector2 DRAW_FONT_POSITION = { -70.0f,0.0f };

	const int GAMESET_FONT_SCALE = 2;
	const float PLAYER_FONT_SCALE = 1.5f;
	const int GAMESET_FONT_OFFSET = 3;
	const float VALUE_MULTIPLY_IN_SPEED = 1.05f;//�J�����X�s�[�h�Ɍ�����l
	const int CAMERA_SHORTEST_RANGE = -500;
	const int CURSOR_SPRITE_WIDTH = 64;
	const int CURSOR_SPRITE_HEIGHT = 28;
	const int CURSOR_SPEED = 0.1f;
}

ResultScene::~ResultScene()
{
	
	DeleteGO(m_retriFontRender);
	DeleteGO(m_backMenuFontRender);
	DeleteGO(m_backTitleFontRender);
	DeleteGO(m_cursorSprite);
	DeleteGO(m_resultBGM);
}

bool ResultScene::Start()
{
	m_BG = FindGO<BackGround>("backGround");//�o�b�N�O���E���h���Q��
	m_gameScene = FindGO<GameScene>("gameScene");//�Q�[���V�[�����Q��
	//�Q�[���Z�b�g���A�^�C���A�b�v��\������
	m_gameSetFontRender = NewGO<FontRender>(0);
	m_gameSetFontRender->SetPosition({ GAMESET_FONT_POSITION });
	m_gameSetFontRender->SetScale(GAMESET_FONT_SCALE);
	m_gameSetFontRender->SetShadowFlag(true);
	m_gameSetFontRender->SetShadowOffset(GAMESET_FONT_OFFSET);
	m_gameSetFontRender->SetShadowColor({ Vector4::Black });

	if (m_resultState == enGameSet)
		m_gameSetFontRender->SetText(L"GAME SET");
	else if (m_resultState == enTimeUp)
		m_gameSetFontRender->SetText(L"TIME  UP");
	else 
		m_gameSetFontRender->SetText(L"H O  G E");
	//��C�N���X������
	QueryGOs<BalloonAir>("balloonAir", [this](BalloonAir* balloonAir)->bool {
		DeleteGO(balloonAir);
		return true;
		});
	return true;
}
void ResultScene::Update()
{
	switch (m_resultState)
	{
	case enGameSet:
		GameSet();//�����������Ƃ��A�������͓����Ɏ��񂾂Ƃ�
		break;		
	case enZoomWinner://���҂ɃJ���������
		ZoomWinner();
		break;
	case enTimeUp://���Ԑ؂�
		TimeUp();
		break;
	case enDraw://���҂����Ȃ��Ƃ�
		Draw();
		break;
	case enMenu://���j���[�I��
		Menu();
		break;
	}
}

//�Q�[���Ɍ������������A�������͓����Ɏ��񂾂Ƃ��̏���
void ResultScene::GameSet()
{
	if (m_gameSetDisplayedTime > 0)//�Q�[���Z�b�g�t�H���g���\������Ă����
	{
		m_gameSetDisplayedTime--;
		return;
	}
	else
	{
		if (m_winnerPl != nullptr)//���҂�����Ƃ�
		{			
			DeleteGO(m_gameSetFontRender);//�t�H���g������
			//���҂̃v���C���[�ԍ���\������
			m_winFontRender = NewGO<FontRender>(0);				
			m_winFontRender->SetScale(GAMESET_FONT_SCALE);
			m_winFontRender->SetText(L"PLAYER " + std::to_wstring(m_winnerPl->GetPlayerNum() + 1) + L" WIN!!");
			m_winFontRender->SetPosition({ WIN_FONT_POSITION });
			m_winFontRender->SetShadowFlag(true);
			m_winFontRender->SetShadowOffset(GAMESET_FONT_OFFSET);
			m_winFontRender->SetShadowColor({ m_winnerPl->GetPlColor() });

			m_winnerPl->SetPosition(m_winnerPos);//���җp�̈ʒu�ɐݒ肷��
			m_winnerPl->SetMoveSpeed(Vector3::Zero);//�X�s�[�h���[���ɂ���
			m_winnerPl->Tilt();//�X�����[���ɂ���
			m_winnerPl->SetArrowScele({ 0.0f,0.0f,0.0f });//�����[���ɂ���
			m_resultState = enZoomWinner;//�Y�[������
		}		
		else//�����Ɏ��񂾂Ƃ�
		{
			DeleteGO(m_gameSetFontRender);//�Q�[���Z�b�g�t�H���g������
			//��ʂ�DRAW�ƕ\������
			m_winFontRender = NewGO<FontRender>(0);
			m_winFontRender->SetScale(GAMESET_FONT_SCALE);
			m_winFontRender->SetText(L"DRAW");
			m_winFontRender->SetPosition({ DRAW_FONT_POSITION });
			m_winFontRender->SetShadowFlag(true);
			m_winFontRender->SetShadowOffset(GAMESET_FONT_OFFSET);
			m_winFontRender->SetShadowColor({Vector4::Black});
			m_resultState = enDraw;//�h���[����ɂ���
		}

		EraseUnused();//����Ȃ����̂�����
	}
}

void ResultScene::ZoomWinner()
{
	if (m_resultBGMFlg == false)//���U���gBGM�𗬂�
	{
		m_resultBGMFlg = true;
		m_resultBGM = NewGO<SoundSource>(0);
		m_resultBGM->Init(L"Assets/sound/���U���gBGM.wav");
		m_resultBGM->SetVolume(SOUND_RESULT_BGM_VOLUME);
		m_resultBGM->Play(true);
		g_camera3D->SetTarget({ CAMERA_TARGET_POSITION });
	}
	
	if (m_winDisplayedTime > 0)//WIN���\������Ă����
	{
		m_winDisplayedTime--;
		m_cameraMoveSpeed = m_cameraMoveSpeed * VALUE_MULTIPLY_IN_SPEED;//�w���֐��I�ɃJ�������ߊ���Ă���
		m_cameraPos.z += m_cameraMoveSpeed;
		
		if (m_cameraPos.z > CAMERA_SHORTEST_RANGE)//�߂Â������Ȃ��悤�ɂ���
		{
			m_cameraPos.z = CAMERA_SHORTEST_RANGE;//�Œ肷��
		}
		g_camera3D->SetPosition(m_cameraPos);
		return;
	}
	else if (g_pad[0]->IsTrigger(enButtonA) || m_winDisplayedTime <= 0)//A�{�^�����������A���Ԃ�����
	{
		m_resultState = enMenu;//���j���[��ʂɈڍs����
		DeleteGO(m_winFontRender);//Win������

		m_cursorSprite = NewGO<SpriteRender>(3);//�J�[�\�����o��
		m_cursorSprite->Init("Assets/Image/Cursor.DDS", CURSOR_SPRITE_WIDTH, CURSOR_SPRITE_HEIGHT);
		m_cursorSprite->SetPosition(RESULT_CURSOR_FONT_INI_POS);
		m_cursorSprite->SetScale({Vector3::One});

		m_retriFontRender = NewGO<FontRender>(1);
		m_retriFontRender->SetPosition(RETRI_FONT_POS);
		m_retriFontRender->SetText(L"������x�V�ԁB");
		m_retriFontRender->SetShadowFlag(true);
		m_retriFontRender->SetShadowColor({ 0.0f,0.0f,0.0f,1.0f });

		m_backMenuFontRender = NewGO<FontRender>(1);//���j���[
		m_backMenuFontRender->SetPosition(BACK_MENU_FONT_POS);
		m_backMenuFontRender->SetText(L"���j���[�֖߂�B");
		m_backMenuFontRender->SetShadowFlag(true);
		m_backMenuFontRender->SetShadowColor({ Vector4::Black });

		m_backTitleFontRender = NewGO<FontRender>(3);//�^�C�g��
		m_backTitleFontRender->SetPosition(BACK_TITLE_FONT_POS);
		m_backTitleFontRender->SetText(L"�^�C�g���֖߂�B");
		m_backTitleFontRender->SetShadowFlag(true);
		m_backTitleFontRender->SetShadowColor({ Vector4::Black });

	
	}
}

//�^�C���A�b�v���̏���
void ResultScene::TimeUp()
{
	if (m_timeUpDisplayedTime > 0)//�^�C���A�b�v�ɂȂ�܂�
	{
		m_timeUpDisplayedTime--;
		return;
	}
	else//�^�C���A�b�v����
	{
		DeleteGO(m_gameSetFontRender);//�Q�[���Z�b�g�t�H���g������
		//DRAW�ƕ\������
		m_winFontRender = NewGO<FontRender>(0);
		m_winFontRender->SetScale(GAMESET_FONT_SCALE);
		m_winFontRender->SetText(L"DRAW");
		m_winFontRender->SetPosition({ 0.0f,-50.0f });
		m_winFontRender->SetShadowFlag(true);
		m_winFontRender->SetShadowOffset(GAMESET_FONT_OFFSET);
		m_winFontRender->SetShadowColor({ Vector4::Black });

		m_resultState = enDraw;//�h���[����ɂ���

		EraseUnused();//����Ȃ����̂�����
		//�v���C���[��T��
		QueryGOs<Player>("player", [this](Player* player)->bool {	
			player->ReturnIniPosition();//�ʒu��ݒ肷��
			player->SetMoveSpeed(Vector3::Zero);//�X�s�[�h���[���ɂ���
			player->Tilt();//�X�����[���ɂ���
			player->SetArrowScele({0.0f,0.0f,0.0f});//�����[���ɂ���

			FontRender* plFont = NewGO<FontRender>(1, "plFont");//�N���c���Ă��邩�m�F���邽�߂Ƀv���C���[�̔ԍ���\������
			plFont->SetText(L"P" + std::to_wstring(player->GetPlayerNum() + 1));//��P��
			plFont->SetPosition(m_plFontPos);//
			plFont->SetScale(PLAYER_FONT_SCALE);
			plFont->SetShadowFlag(true);
			plFont->SetShadowOffset(GAMESET_FONT_OFFSET);
			plFont->SetShadowColor(player->GetPlColor());

			m_plFontPos.x += 80.0f;//���̃t�H���g�̂��߂Ɉʒu�����炷
			return true;
			});

		g_camera3D->SetPosition({ -4000.0f,500.0f,0.0f });//�J�����̈ʒu��ݒ�
	}
}

void ResultScene::Draw()//�h���[����̂Ƃ�
{
	if (m_drawDisplayedTime > 0)//�h���[�t�H���g���\������Ă����
	{
		m_drawDisplayedTime--;
	}
	Vector3 right = g_camera3D->GetRight();//�J�����̉E�������擾
	Vector3 cameraPos = g_camera3D->GetPosition();//�J�����̈ʒu���擾
	cameraPos += right * 40.0f;//�J�����̈ʒu���X�e�[�W�̒��S�����ɉE�ɉ�]������
	g_camera3D->SetPosition(cameraPos);//�ʒu��ݒ�
		
	if (g_pad[0]->IsTrigger(enButtonA) || m_drawDisplayedTime <= 0)//A�{�^�����������A���Ԃ�����
	{
		m_resultState = enMenu;//���j���[�I���Ɉڂ�
		DeleteGO(m_winFontRender);//�h���[�t�H���g������
		//�����c�����v���C���[�\��������
		QueryGOs<FontRender>("plFont", [this](FontRender* plFont)->bool {
			DeleteGO(plFont);
			return true;
			});
		//�J�[�\����\������
		m_cursorSprite = NewGO<SpriteRender>(3);
		m_cursorSprite->Init("Assets/Image/Cursor.DDS", 64, 28);
		m_cursorSprite->SetPosition(RESULT_CURSOR_FONT_INI_POS);

		m_retriFontRender = NewGO<FontRender>(1);
		m_retriFontRender->SetPosition(RETRI_FONT_POS);
		m_retriFontRender->SetText(L"������x�V�ԁB");
		m_retriFontRender->SetShadowFlag(true);
		m_retriFontRender->SetShadowColor({ 0.0f,0.0f,0.0f,1.0f });
		//���j���[
		m_backMenuFontRender = NewGO<FontRender>(1);
		m_backMenuFontRender->SetPosition(BACK_MENU_FONT_POS);
		m_backMenuFontRender->SetText(L"���j���[�֖߂�B");
		m_backMenuFontRender->SetShadowFlag(true);
		m_backMenuFontRender->SetShadowColor({ 0.0f,0.0f,0.0f,1.0f });
		//�^�C�g��
		m_backTitleFontRender = NewGO<FontRender>(1);
		m_backTitleFontRender->SetPosition(BACK_TITLE_FONT_POS);
		m_backTitleFontRender->SetText(L"�^�C�g���֖߂�B");
		m_backTitleFontRender->SetShadowFlag(true);
		m_backTitleFontRender->SetShadowColor({ 0.0f,0.0f,0.0f,1.0f });

		m_lookStageFlag = true;//�J�������񂷂��ǂ���
	}
}

/// @brief ���j���[�\�����
void ResultScene::Menu()
{
	SetCursorPos();//�J�[�\�����ړ�������

	if (g_pad[0]->IsTrigger(enButtonA))//A��������
	{	
		m_resultSE = NewGO<SoundSource>(0);//�����o��
		m_resultSE->Init(L"Assets/sound/���U���g���艹.wav");
		m_resultSE->SetVolume(SOUND_RESULT_SE_VOLUME);
		m_resultSE->Play(false);
		if (m_selectMenu == enRetri)//���g���C��������
		{
			//�c���Ă���v���C���[������
			QueryGOs<Player>("player", [this](Player* player)->bool {
				if (player != nullptr)
					DeleteGO(player);
				return true;
				});
			
			m_gameScene->SetIniPosition();//���g���C����::�v���C���[���쐬
			m_gameScene->SetGameState(GAME_STATE_LOOK_STAGE);//�Q�[���V�[���̏�Ԃ��X�V����::�X�e�[�W�����n��
			m_stageNum = m_BG->GetStageNum();//�����X�e�[�W�Ń��g���C����
			m_BG->SetIniPosition();//�v���C���[�̏����ʒu�����x���Őݒ肷��
			DeleteGO(m_BG);//�o�b�N�O���E���h���쐬������::
			BackGround* backGround = NewGO<BackGround>(0, "backGround");
			backGround->SetStageNum(m_stageNum);//�����X�e�[�W��ݒ肷��
			NewGO<UIDisplay>(0, "UIdisplay");//UI��\��������
			DeleteGO(this);//���U���g�V�[��������
		}
		else if (m_selectMenu == enBackMenu)//���j���[��������
		{
			DeleteGO(m_gameScene);//�Q�[���V�[��������			
			DeleteGO(m_BG);//�o�b�N�O���E���h������
			//�v���C���[������
			QueryGOs<Player>("player", [this](Player* player)->bool {
				DeleteGO(player);
				return true;
				});
			DeleteGO(this);//���U���g�V�[��������
			NewGO<TitleBack>(0, "titleBack");//�^�C�g���w�i���쐬����
			NewGO<SelectScene>(0, "selectScene");//�I����ʂ��쐬����
		}
		else if (m_selectMenu == enBackTitle)//�^�C�g����������
		{
			DeleteGO(m_gameScene);//�Q�[���V�[��������			
			DeleteGO(m_BG);//�o�b�N�O���E���h������
			//�v���C���[������
			QueryGOs<Player>("player", [this](Player* player)->bool {
				DeleteGO(player);
				return true;
				});
			DeleteGO(this);//���U���g�V�[��������
			NewGO<TitleBack>(0, "titleBack");//�^�C�g���w�i���쐬����
			NewGO<TitleScene>(0, "titleScene");//�^�C�g�����쐬����
		}
	}
	
	if (m_lookStageFlag == true)
	{//�X�e�[�W�̒��S�����ɃJ��������]������
		Vector3 right = g_camera3D->GetRight();
		Vector3 cameraPos = g_camera3D->GetPosition();
		cameraPos += right * 40.0f;
		g_camera3D->SetPosition(cameraPos);
	}
}
//�J�[�\���̈ʒu�����߂�B
void ResultScene::SetCursorPos()
{
	if (g_pad[0]->IsTrigger(enButtonDown))//���{�^����������
	{
		//�����o��
		m_resultSE = NewGO<SoundSource>(0);
		m_resultSE->Init(L"Assets/sound/���U���g�I����.wav");
		m_resultSE->SetVolume(SOUND_RESULT_SE_VOLUME);
		m_resultSE->Play(false);

		isSelectMenu(false);
	}
	else if (g_pad[0]->IsTrigger(enButtonUp))//��{�^����������
	{
		//�����o��
		m_resultSE = NewGO<SoundSource>(0);
		m_resultSE->Init(L"Assets/sound/���U���g�I����.wav");
		m_resultSE->SetVolume(SOUND_RESULT_SE_VOLUME);
		m_resultSE->Play(false);

		isSelectMenu(true);
	}

	//�J�[�\���̍��E�̓���
	m_cursorMoveSpeedX += 0.1;
	m_cursorPos.x += pow(m_cursorMoveSpeedX,0.5f) ;
	
	if (m_cursorPos.x > CURSOR_FONT_MAX_POS_X)	//�J�[�\���̓��������Z�b�g����B
	{
		m_cursorMoveSpeedX = INI_CURSOR_MOVE_SPEED_X;
		m_cursorPos.x = RESULT_CURSOR_FONT_INI_POS.x;
	}
	m_cursorSprite->SetPosition(m_cursorPos);
}

//�J�[�\���̈ʒu���㉺�Ɉړ�����B
void ResultScene::isSelectMenu(bool isUp)
{
	if (isUp == true)
	{
		if (m_selectMenu == enRetri)
		{
			m_selectMenu = enBackTitle;
		}
		else if (m_selectMenu == enBackMenu)
		{
			m_selectMenu = enRetri;
		}
		else if(m_selectMenu == enBackTitle)
		{
			m_selectMenu = enBackMenu;
		}
	}
	else if (isUp == false)
	{
		if (m_selectMenu == enRetri)
		{
			m_selectMenu = enBackMenu;
		}
		else if (m_selectMenu == enBackMenu)
		{
			m_selectMenu = enBackTitle;
		}
		else if(m_selectMenu == enBackTitle)
		{
			m_selectMenu = enRetri;
		}
	}
	
	switch (m_selectMenu)
	{
	case enRetri:
		m_cursorPos.y = RETRI_FONT_POS.y - 20;
		break;
	case enBackMenu:
		m_cursorPos.y = BACK_MENU_FONT_POS.y - 20;
		break;
	case enBackTitle:
		m_cursorPos.y = BACK_TITLE_FONT_POS.y - 20;
		break;
	}
}

void ResultScene::EraseUnused()
{
	//���DUI������
	QueryGOs<UIDisplay>("UIdisplay", [this](UIDisplay* UIdisplay)->bool {
		DeleteGO(UIdisplay);
		return true;
		});
	//���Ԃ�����
	QueryGOs<WindTurbine>("windTurbine", [this](WindTurbine* windTurbine)->bool {
		DeleteGO(windTurbine);
		return true;
		});
	//��������
	QueryGOs<GimmickNeedle>("gimmickNeedle", [this](GimmickNeedle* gimmickNeedle)->bool {
		DeleteGO(gimmickNeedle);
		return true;
		});
	//�^�C���\��������
	QueryGOs<GameTimer>("gameTimer", [this](GameTimer* gameTimer)->bool {
		DeleteGO(gameTimer);
		return true;
		});
}