#pragma once
namespace
{
	const Vector3 EXIT_INI_POS = { -300,-200,0 };
	const Vector3 START_INI_POS = { 0,-200,0 };
	const Vector3 OPTION_INI_POS = { 300,-200,0 };
	const Vector3 BALLOON_SIZE = { 0.7f,0.7f,1.0f };
	const int BALLOON_INI_POSY = -200;
	const float SOUND_BGM_TITLE_VOLUME = 0.2f;
}
class TitleScene : public IGameObject
{
public:
	bool Start();
	void Update();
	~TitleScene();
	
private:

	SpriteRender* m_title_Sprite;
	SpriteRender* m_start_Sprite;
	SpriteRender* m_option_Sprite;
	SpriteRender* m_exit_Sprite;
	
	Vector3 m_exitPos = { -300,-200,0 };
	Vector3 m_startPos = { 0,-200,0 };
	Vector3 m_optionPos = { 300,-200,0 };
	
	SoundSource* ss = nullptr;

	int m_selectNum = 1;
	float m_selectLoopCount = 0;

	bool FloatingFlg = true;

	int m_playerCount = 2;

	bool m_endOn = false;
	int m_endCount = 0;
};

