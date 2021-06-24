#pragma once
class Player;
#include "Player.h"
namespace
{
	const int INI_AIR_VOLUME = 70;//風船の空気の量の初期値
	const int MAX_BALLOON_SIZE = 350;	//風船の空気の量の最大量
	const int MIN_BALLOON_SIZE = 10;	//風船の空気の量の最小量
	const float BRAKE_POWER = 0.1;	//ブレーキを行った際にm_moveSpeedにかける値
	const float AIR_COST_BOOST = 0.5f;	//空気を噴射しているときに、1フレームで減る空気量
}

class BalloonAir : public IGameObject
{
private:
	Player* m_parent = nullptr;
	int m_parentNum = 0;
	float m_airVolume = INI_AIR_VOLUME;//風船の大きさ(幅)

public:
	bool Start();
	void Update();

	void SetParent(Player* p) { m_parent = p; };	//親となる風船を設定。
	void SetParentNum(int num) { m_parentNum = num; };
	void Air();	//風船の空気に関する関数

	void AddAir(float air);		//airの値分、空気を入れる
	void BleedAir(float air);	//airの値分、空気を抜く

};

