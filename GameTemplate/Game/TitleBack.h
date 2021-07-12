#pragma once
class TitleScene;
class TitleBack:public IGameObject
{
public:
	bool Start();
	void Update();
	~TitleBack();
	
	void SetDestroy(bool flag) { m_destroy = flag; }
private:
	TitleScene* titleScene;

	SpriteRender* m_back_Sprite;
	SpriteRender* m_cloud1_Sprite;
	SpriteRender* m_cloud2_Sprite;
	SpriteRender* m_undercloud01_Sprite;
	SpriteRender* m_undercloud02_Sprite;
	SpriteRender* m_undercloud11_Sprite;
	SpriteRender* m_undercloud12_Sprite;
	SpriteRender* m_undercloud21_Sprite;
	SpriteRender* m_undercloud22_Sprite;


	Vector3 m_backPos = { Vector3::Zero };
	Vector3 m_cloud1Pos = { Vector3::Zero };
	Vector3 m_cloud2Pos = { 1280,0,0 };
	Vector3 m_undercloud01Pos = { Vector3::Zero };
	Vector3 m_undercloud02Pos = { -1280,0,0 };
	Vector3 m_undercloud11Pos = { Vector3::Zero };
	Vector3 m_undercloud12Pos = { -1280,0,0 };
	Vector3 m_undercloud21Pos = { Vector3::Zero };
	Vector3 m_undercloud22Pos = { -1280,0,0 };

	SoundSource* m_titleBGM = nullptr;	//BGMのサウンドソース

	float m_BM_MoveSpeed = 1.0;
	bool m_destroy = false;
};

