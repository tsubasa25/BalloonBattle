#pragma once
namespace 
{
	const Vector3 EXIT_INI_POS={ -300,-200,0 };
	const Vector3 START_INI_POS = { 0,-200,0 };
	const Vector3 OPTION_INI_POS = { 300,-200,0 };
	const Vector3 BALLOON_SIZE = { 0.7f,0.7f,1.0f };
	const int BALLOON_INI_POSY = -200;
}
class TitleScene : public IGameObject
{
public:
	bool Start();
	void Update();
	~TitleScene();	

private:
	SpriteRender* m_title_Sprite = NewGO<SpriteRender>(0);
	SpriteRender* m_start_Sprite = NewGO<SpriteRender>(1);
	SpriteRender* m_option_Sprite = NewGO<SpriteRender>(1);
	SpriteRender* m_exit_Sprite = NewGO<SpriteRender>(1);

	Vector3 m_exitPos = { -300,-200,0 };
	Vector3 m_startPos = { 0,-200,0 };
	Vector3 m_optionPos = { 300,-200,0 };
	
	int m_playerCount = 4;
	int m_selectNum = 1;
	float m_selectLoopCount = 0;
};

