#pragma once
namespace
{
	const Vector3 BUIL_BALL_POS = {200,50,0};
	const float BUIL_BALL_POSY = 50;
	const Vector3 SKY_BALL_POS = {500,50,0};
	const Vector3 TRAP_BALL_POS = { 200,-200,0 };
	const float TRAP_BALL_POSY = -200;
	const Vector3 RANDAM_BALL_POS{ 500,-200,0 };
	const Vector3 P1_POS = { -550,100,0 };
	const Vector3 P2_POS = { -410,100,0 };
	const Vector3 P3_POS = { -270,100,0 };
	const Vector3 P4_POS = { -130,100,0 };
	const Vector3 P5_POS = { -550,-80,0 };
	const Vector3 P6_POS = { -410,-80,0 };
	const Vector3 P7_POS = { -270,-80,0 };
	const Vector3 P8_POS = { -130,-80,0 };

}
class SelectScene:public IGameObject
{
public:
	bool Start();
	void Update();
	~SelectScene();
private:
	SpriteRender* m_cPlayerCount_Sprite;//数字画像
	SpriteRender* m_cStockNum_Sprite;

	SpriteRender* m_okPlayer_Sprite;//OK画像
	SpriteRender* m_okStok_Sprite;

	SpriteRender* m_arrowPlayer_Sprite;//<<>>画像
	SpriteRender* m_arrowStock_Sprite;

	SpriteRender* m_cPlayer_Sprite;//雲文字プレイヤー
	SpriteRender* m_cStock_Sprite;//雲文字ストック
	SpriteRender* m_cStage_Sprite;//雲文字ステージ

	//ステージ画像
	SpriteRender* m_stageBalloon_Sprite[4] = { nullptr,nullptr,nullptr,nullptr };
	//空島
	//ビル
	//トラップ
	//おまかせ

	//プレイヤーの風船画像
	SpriteRender* m_playerUI_Sprite[8] = { nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr };
	

	Vector3 m_cPlayerPos = {-350,250,0};
	Vector3 m_cStockPos = {-350,-250,0};
	Vector3 m_StagePos = {350,250,0};

	Vector3 m_cPlayerNumPos = { 0,250,0 };
	Vector3 m_cStockNumPos = { 0,-250,0 };

	Vector3 m_arrowPlayerPos = { 0,250,0 };
	Vector3 m_arrowStockPos = {0,-250,0};

	Vector3 m_okPlayerPos = { 0,250,0 };
	Vector3 m_okStockPos = { 0,-250,0 };

	Vector3 m_stageBalloonPos[4] = { {SKY_BALL_POS},{BUIL_BALL_POS},{TRAP_BALL_POS},{RANDAM_BALL_POS} };

	Vector3 m_playerUIPos[8] = { { P1_POS },{ P2_POS },{ P3_POS },{ P4_POS },{ P5_POS },{ P6_POS },{ P7_POS },{ P8_POS } };

	enum TitleState
	{
		enPlayerNum,//プレイヤー人数選択状態
		enPlayerStock,//プレイヤーストック選択状態
		enStageSelect//ステージ選択状態
	};
	TitleState m_titleState=enPlayerNum;
	int m_playerCount = 2;
	int m_playerStock = 3;
	bool m_selectNum[2][2] = { {0,0},{0,0} };
	int m_XNum = 0;
	int m_YNum = 0;
	float m_selectLoopCount = 0;
	int m_stageNum = 0;
};

