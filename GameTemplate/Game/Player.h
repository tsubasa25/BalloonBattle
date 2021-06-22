#pragma once
#include<vector>
namespace
{
	const int STAGE_WIDTH = 750;
	const int STAGE_DEPTH = 750;	
	const int INI_BALLOON_SIZE = 70;//風船の大きさの初期値
	const int MAX_BALLOON_SIZE = 350;	//風船が大きくなれる最大サイズ
	const int MIN_BALLOON_SIZE = 10;	//風船が小さくなれる最大サイズ
	const int MASS_DIVISOR = 20;//風船の大きさから質量を出すときの割る値
	const float REBOUND_POWER = 2;//敵と衝突したとき、勢いにかける値
	const float BRAKE_POWER = 0.1;	//ブレーキを行った際にm_moveSpeedにかける値
}
class Player:public IGameObject
{
private:
	
	Vector3 m_scale = { Vector3::Zero };
	int m_playerNum = 0;//プレイヤー番号
	int m_stock = 3;//ストック
	int m_playerCount = 0;
	FontRender* m_PosX_font = NewGO<FontRender>(0);//デバッグ用
	FontRender* m_PosY_font = NewGO<FontRender>(0);
	FontRender* m_PosZ_font = NewGO<FontRender>(0);
	FontRender* m_Size_font = NewGO<FontRender>(0);
	PointLight* pointLight = NewGO<PointLight>(0);	
	
	Vector3 m_position = { Vector3::Zero };
	Vector3 m_iniPos= { Vector3::Zero };
	Vector3 m_decele = { Vector3::Zero };
	Vector3 m_moveSpeed = { Vector3::Zero };

	CharacterController m_charaCon;//プレイヤーのキャラコン

	SkinModelRender* m_skinModelRender = nullptr;
	

	float m_balloonSize = INI_BALLOON_SIZE;//風船の大きさ(幅)
	bool m_enemyHit = false;//敵とあたったとき		
public:
	std::vector<Player*> m_enemy;
	std::vector<Player*>::iterator it;
	~Player();
	bool Start();
	void Update();

	void SetPlayerNum(int num) { m_playerNum = num; }//プレイヤー番号を設定する
	int GetPlayerNum() { return m_playerNum; }//プレイヤー番号を入手する

	void SetPlayerCount(int num) { m_playerCount = num; }//プレイヤー人数を設定する

	void SetEnemy(Player* enemy, int i) { m_enemy[i] = enemy; }//敵情報を設定する

	void SetIniPosition(Vector3 pos) { m_position = pos; m_iniPos = pos; }//初期位置を設定
	void SetPosition(Vector3 pos) { m_skinModelRender->SetPosition(pos); m_position = pos; }
	Vector3 GetPosition() { return m_position; }

	void SetScale(Vector3 scale) { m_skinModelRender->SetScale(scale); }//大きさ
	Vector3 GetScale() { return m_skinModelRender->GetScale(); }

	Vector3 Decele(Vector3 decele);//減速処理
	
	float GetStageWidth() { return STAGE_WIDTH; }//ステージの横幅
	float GetStageDepth() { return STAGE_DEPTH; }//ステージの縦幅

	void SetMoveSpeed(Vector3 dir) { m_moveSpeed += dir; }//コントローラー入力の値を加算合計する
	void ResetMoveSpeed(Vector3 dir) { m_moveSpeed = dir; }//再設定する
	Vector3 GetMoveSpeed() { return m_moveSpeed; }
	
	void Move();//移動関数

	void HitWall();//壁にあたったとき

	void HitPlayer();//プレイヤーに合ったとき
	
	Vector3 ReboundSpeed();//モデルの法線から反射する方向を求めて移動方向を決定する

	void Air();	//風船の空気に関する関数

	void AddAir(float air);		//airの値分、空気を入れる
	void BleedAir(float air);	//airの値分、空気を抜く

	//デバッグ用
	void Debug(int pNum);
	int m_oldStock = m_stock;
	bool m_IsArrowOn = true;//矢印を表示するか
	bool m_IsAIOn = false;//敵が自分めがけて突進してくる
	SkinModelRender* m_skinModelRenderArrow = nullptr;
	Quaternion m_rot;
	Vector3 m_arrowSize = Vector3::One;
	Vector3 m_oldPos = Vector3::Zero;

};

