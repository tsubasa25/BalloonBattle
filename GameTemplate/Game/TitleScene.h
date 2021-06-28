#pragma once
namespace 
{
	const Vector4 TITLE_COLOR = { 1,0,0,0 };//�^�C�g���̐F
	const Vector4 CHOOSING_COLOR = { 0,1,1,0 };//�I�𒆂̐F
	const Vector4 NOTCHOOSING_COLOR = { 1,1,1,0 };//�I������ĂȂ����̐F
	const Vector2 SPRITE_TITLE_POSITION = { -250,200 };//�^�C�g���̈ʒu
	const Vector2 SPRITE_START_POSITION = { -85,0 };//�X�^�[�g�{�^���̈ʒu
	const Vector2 SPRITE_PLAYERNUM_POSITION = { -100,-100 };//�v���C���[�l���ݒ�{�^���̈ʒu
	const Vector2 SPRITE_PLAYERCOUNT_POSITION = { 200,-100 };//�v���C���[�l���̈ʒu
	const Vector2 SPRITE_EXIT_POSITION = { -70,-200 };//�Q�[���I���{�^���̈ʒu
	const int SPRITE_TITLE_SCALE = 2;//�^�C�g���̑傫��
	const int SPRITE_START_SCALE = 1;//�X�^�[�g�{�^���̑傫��
	const int SPRITE_PLAYERNUM_SCALE = 1;//�v���C���[�l���ݒ�{�^���̑傫��
	const int SPRITE_PLAYERCOUNT_SCALE = 1;//�v���C���[�l���̑傫��
	const int SPRITE_EXIT_SCALE = 1;//�Q�[���I���{�^���̑傫��
	const int MIN_PLAYERCOUNT = 1;//�Œ�v���C���[�l��
	const int MAX_PLAYERCOUNT = 8;//�ő�v���C���[�l��
}
class TitleScene : public IGameObject
{
public:
	bool Start();
	void Update();
	~TitleScene();

private:
	FontRender* m_title_FontRender = NewGO<FontRender>(0);//�^�C�g���̕���
	std::wstring m_title = L"BALLOON BATTLE";
	FontRender* m_playernumber_FontRender = NewGO<FontRender>(0);//�^�C�g���̕���
	std::wstring m_playernumber = L"PLAYER";
	FontRender* m_start_FontRender = NewGO<FontRender>(0);//�^�C�g���̕���
	std::wstring m_start = L"START";
	FontRender* m_exit_FontRender = NewGO<FontRender>(0);//�^�C�g���̕���
	std::wstring m_exit = L"EXIT";

	FontRender* m_playerCount_FontRender = NewGO<FontRender>(0);//�^�C�g���̕���

	int m_playerCount = 4;
	int m_selectNum = 0;

};

