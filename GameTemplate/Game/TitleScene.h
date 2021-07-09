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
	void BackMove();

private:
	SpriteRender* m_back_Sprite;
	SpriteRender* m_cloud1_Sprite;
	SpriteRender* m_cloud2_Sprite;
	SpriteRender* m_undercloud01_Sprite;
	SpriteRender* m_undercloud02_Sprite;
	SpriteRender* m_undercloud11_Sprite;
	SpriteRender* m_undercloud12_Sprite;
	SpriteRender* m_undercloud21_Sprite;
	SpriteRender* m_undercloud22_Sprite;

	SpriteRender* m_title_Sprite;
	SpriteRender* m_start_Sprite;
	SpriteRender* m_option_Sprite;
	SpriteRender* m_exit_Sprite;
	
	Vector3 m_backPos = { Vector3::Zero };
	Vector3 m_cloud1Pos = { Vector3::Zero };
	Vector3 m_cloud2Pos = { 1280,0,0 };
	Vector3 m_undercloud01Pos = {  Vector3::Zero };
	Vector3 m_undercloud02Pos = { -1280,0,0};
	Vector3 m_undercloud11Pos = { Vector3::Zero};
	Vector3 m_undercloud12Pos = {  -1280,0,0 };
	Vector3 m_undercloud21Pos = { Vector3::Zero };
	Vector3 m_undercloud22Pos = { -1280,0,0 };

	Vector3 m_exitPos = { -300,-200,0 };
	Vector3 m_startPos = { 0,-200,0 };
	Vector3 m_optionPos = { 300,-200,0 };

	SoundSource* ss = nullptr;

	int m_selectNum = 1;
	float m_selectLoopCount = 0;

	bool FloatingFlg = true;

int m_playerCount = 2;

	float m_BM_MoveSpeed = 1.0;public:
	SoundSource* m_titleBGM = nullptr;						//BGMのサウンドソース
};

