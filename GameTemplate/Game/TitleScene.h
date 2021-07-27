#pragma once
namespace
{
	const Vector3 EXIT_INI_POS = { -300,-200,0 };
	const Vector3 START_INI_POS = { 0,-200,0 };
	const Vector3 OPTION_INI_POS = { 300,-200,0 };
	const Vector3 BALLOON_SIZE = { 0.7f,0.7f,1.0f };
	const int BALLOON_INI_POSY = -200;

	const float SOUND_TITLE_SE_VOLUME = 1.0f;
	const float SOUND_TITLE_BGM_VOLUME = 0.2f;
	const float SOUND_TITLE_FLOAT_SE_VOLUME = 0.2f;
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
	
	Vector3 m_exitPos = { EXIT_INI_POS };
	Vector3 m_startPos = { START_INI_POS };
	Vector3 m_optionPos = { OPTION_INI_POS };
	
	SoundSource* ss = nullptr;
	SoundSource* m_titleBGM = nullptr;
	
	int m_selectNum = 1;			//選択している番号
	float m_selectLoopCount = 0;	//sin用ループカウント

	bool FloatingFlg = true;		//音を鳴らすためのフラグ

	bool m_isEnd = false;			//STARTを押したとき	
	int m_endCount = 0;				//風船が上に行くようのループカウント
};

