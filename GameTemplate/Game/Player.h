#pragma once
class BalloonAir;
class BackGround;
#include<vector>
#include "BalloonAir.h"
namespace
{
	const int STAGE_WIDTH = 750;
	const int STAGE_DEPTH = 750;
	const int MASS_DIVISOR = 20;//風船の大きさから質量を出すときの割る値
	const float REBOUND_POWER = 1.5;//敵と衝突したとき、勢いにかける値
	const int INI_AIR_VOLUME = 70;//風船の空気の量の初期値
	const Vector3 POINTLIGHT_COLOR = { 10,10,10 };//ポイントライトの色
	const int POINTLIGHT_RANGE = 200;//ポイントライトの影響範囲
	const int DESELE_VOLUME = 3500;//減速させる大きさを調整する値
	const float GRAVITY_SPEED = 0.7f;//落下スピード
	const float GRAVITY_INDEX = 2.0f;//落下スピードにかける指数
	const float PAI = 3.14159f;//円周率
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
	
	bool m_enemyHit = false;//敵とあたったとき		

	BalloonAir* m_myAir = nullptr;

	float m_myAirVolume = INI_AIR_VOLUME;

	Quaternion m_playerRot = {0.0f,0.0f,0.0f,0.0f};
	std::vector<Player*> m_enemy;
	std::vector<Player*>::iterator it;
	BackGround* m_backGround = nullptr;
public:

	
	~Player();
	bool Start();
	void Update();

	void SetPlayerNum(int num) { m_playerNum = num; }//プレイヤー番号を設定する
	int GetPlayerNum() { return m_playerNum; }//プレイヤー番号を入手する

	void SetPlayerCount(int num) { m_playerCount = num; }//プレイヤー人数を設定する

	void SetEnemyData(Player* enemy) { m_enemy.push_back(enemy); }//敵情報を設定する

	void SetIniPosition(Vector3 pos) { m_position = pos; m_iniPos = pos; }//初期位置を設定
	void SetPosition(Vector3 pos) { m_skinModelRender->SetPosition(pos); m_position = pos; }
	Vector3 GetPosition() { return m_position; }

	void SetScale(Vector3 scale) { m_skinModelRender->SetScale(scale); }//大きさ
	Vector3 GetScale() { return m_skinModelRender->GetScale(); }

	Vector3 Decele(Vector3 decele);//減速処理
	
	float GetStageWidth() { return STAGE_WIDTH; }//ステージの横幅
	float GetStageDepth() { return STAGE_DEPTH; }//ステージの縦幅
	
	void AddMoveSpeed(Vector3 dir) { m_moveSpeed += dir; }//コントローラー入力の値を加算合計する
	void SetMoveSpeed(Vector3 dir) { m_moveSpeed = dir; }//再設定する
	Vector3 GetMoveSpeed() { return m_moveSpeed; }
	
	void Move();//移動関数

	void HitWall();//壁にあたったとき

	void HitPlayer();//プレイヤーに合ったとき
	
	Vector3 ReboundSpeed();//モデルの法線から反射する方向を求めて移動方向を決定する

	void SetAirVolume(float air) { m_myAirVolume = air; };	//風船の空気の量を設定

	void Tilt();	//風船の傾きを決める。

	void PlayerDeath();	//キャラクターが死亡したときの処理

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

