#pragma once
#include<vector>
namespace
{
	const int STAGE_WIDTH = 750;
	const int STAGE_DEPTH = 750;
	const int STAGE_HOLE = 350;
	const float INI_BULLOON_SIZE = 70;
}
class Player:public IGameObject
{
private:
	
	Vector3 m_scale = { Vector3::Zero };
	int m_playerNum = 0;//プレイヤー番号
	int m_stock = 1;//ストック
	int m_playerCount = 4;
	FontRender* m_PosX_font = NewGO<FontRender>(0);//デバッグ用
	FontRender* m_PosY_font = NewGO<FontRender>(0);
	FontRender* m_PosZ_font = NewGO<FontRender>(0);
	FontRender* m_Size_font = NewGO<FontRender>(0);

	Vector3 m_position = { Vector3::Zero };
	Vector3 m_iniPos= { Vector3::Zero };
	Vector3 m_decele = { Vector3::Zero };
	Vector3 m_moveDir = { Vector3::Zero };

	CharacterController m_charaCon;//プレイヤーのキャラコン

	SkinModelRender* m_skinModelRender = nullptr;
	

	float m_bulloonSize = 70;
public:		
	std::vector<Player*> m_enemy;
	std::vector<Player*>::iterator it;
	~Player();
	bool Start();
	void Update();

	void SetPlayerNum(int num) { m_playerNum = num; }//プレイヤー番号を設定する
	int GetPlayerNum() { return m_playerNum; }//プレイヤー番号を入手する

	void SetEnemy(Player* enemy, int i) { m_enemy[i] = enemy; }//敵情報を設定する

	void SetIniPosition(Vector3 pos) { m_position = pos; m_iniPos = pos; }//初期位置を設定
	void SetPosition(Vector3 pos) { m_skinModelRender->SetPosition(pos); }
	Vector3 GetPosition() { return m_skinModelRender->GetPosition(); }

	void SetScale(Vector3 scale) { m_skinModelRender->SetScale(scale); }//大きさ
	Vector3 GetScale() { return m_skinModelRender->GetScale(); }

	Vector3 Decele(Vector3 decele);//減速処理
	
	float GetStageWidth() { return STAGE_WIDTH; }//ステージの横幅
	float GetStageDepth() { return STAGE_DEPTH; }//ステージの縦幅

	void SetMoveDir(Vector3 dir) { m_moveDir += dir; }//コントローラー入力の値を加算合計する
	void ResetMoveDir(Vector3 dir) { m_moveDir = dir; }//再設定する
	Vector3 GetMoveDir() { return m_moveDir; }
	
	void Move();//移動関数

	void HitWall();//壁にあたったとき

	void HitPlayer();//プレイヤーに合ったとき
	
	void Debug(int pNum);//デバッグ用
};

