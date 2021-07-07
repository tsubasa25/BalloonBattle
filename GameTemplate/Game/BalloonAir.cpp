#include "stdafx.h"
#include "BalloonAir.h"
#include "Player.h"
bool BalloonAir::Start()
{
	return true;
}

void BalloonAir::Update()
{
	Air();	
	m_parent->SetAirVolume(m_airVolume);
}
void BalloonAir::Air()
{
	Vector3 speedToHorizontal = m_parent->GetMoveSpeed();	//水平方向へのスピード(y方向は0)
	speedToHorizontal.y = 0.0f;

	//ブレーキと空気注入の処理
	if (g_pad[m_parentNum]->IsPress(enButtonB))
	{
		//プレイヤーが動いているときにBボタンを押すと、
		if (speedToHorizontal.Length() > 0.0f)
		{
			//ブレーキをかける。
			Vector3 brakeSpeed = m_parent->GetMoveSpeed();
			brakeSpeed.y = 0;
			brakeSpeed *= BRAKE_POWER;
			brakeSpeed *= -1.0f;	//風船のm_moveSpeedに減算するので-1をかける。
			m_parent->AddMoveSpeed(brakeSpeed);
			BleedAir(speedToHorizontal.Length() * AIR_COST_BRAKE);	//ブレーキのデメリットとして空気が抜ける
		}
		else
		{
			//止まっているときにBボタンを押すと、膨む。
			AddAir(ADD_AIR_TO_BALLOON_POWER);
			
			if (InflateFlg == false ) {
				InflateFlg = true;
				ss = NewGO<SoundSource>(0);
				ss->Init(L"Assets/sound/風船を膨らませる音.wav");
				ss->Play(true);
			}
			if (m_airVolume >= MAX_AIR_VOLUME) {
				DeleteGO(ss);
			}
		}
	}
	else if (InflateFlg == true) {
		DeleteGO(ss);
		InflateFlg = false;
	}

	//プレイヤーがスティックを倒しているとき
	if (g_pad[m_parentNum]->GetLStickXF() != 0.0f
		|| g_pad[m_parentNum]->GetLStickYF() != 0.0f)
	{
		//Lスティックの傾きの大きさに応じて、空気が抜ける。
		Vector3 LStickTilt = {
			(g_pad[m_parentNum]->GetLStickXF()),
			(g_pad[m_parentNum]->GetLStickYF()),
			0.0f
		};
		BleedAir(LStickTilt.Length() * AIR_COST_MOVE);

		//Aボタンが押されたら、空気を噴射して一気に加速。
		if (g_pad[m_parentNum]->IsPress(enButtonA))
		{
			Vector3 boostSpeed = m_parent->GetMoveSpeed();		
			boostSpeed.y = 0.0f;

			boostSpeed.x *= ADD_BOOST_POWER;
			boostSpeed.z *= ADD_BOOST_POWER;

			m_parent->AddMoveSpeed(boostSpeed);

			//空気が一定量抜ける。
			BleedAir(AIR_COST_BOOST);

			if (AccelFlg == false) {
				AccelFlg = true;
				ss = NewGO<SoundSource>(0);
				ss->Init(L"Assets/sound/風船が加速する音.wav");
				ss->Play(true);
			}
		}
	}
	if (!g_pad[m_parentNum]->IsPress(enButtonA))
		{
		if (AccelFlg == true) {
			DeleteGO(ss);
			AccelFlg = false;
		}
	}
	if (g_pad[m_parentNum]->IsPress(enButtonY))
	{

		m_parent->AddMoveSpeed(RISE_BOOST_POWER);
		
		//空気が一定量抜ける。
		BleedAir(AIR_COST_RISE_BOOST);
	}
}

//airの値分、風船に空気を加える
void BalloonAir::AddAir(float air)
{
	m_airVolume += air;
	if (m_airVolume > MAX_AIR_VOLUME)	//最大サイズよりは大きくなれない。
		m_airVolume = MAX_AIR_VOLUME;
	
}
//airの値分、風船の空気を抜く
void  BalloonAir::BleedAir(float air)
{
	m_airVolume -= air;
	if (m_airVolume < MIN_AIR_VOLUME)	//最小サイズより小さくなったら、死亡する。
	{
		m_parent->PlayerDeath();
		ss = NewGO<SoundSource>(0);
		ss->Init(L"Assets/sound/風船の萎んで死んだ音.wav");
		ss->Play(false);
	}
}