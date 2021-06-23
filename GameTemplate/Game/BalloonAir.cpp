#include "stdafx.h"
#include "BalloonAir.h"

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
	speedToHorizontal.y = 0;

	//ブレーキと空気注入の処理
	if (g_pad[m_parentNum]->IsPress(enButtonB))
	{
		if (speedToHorizontal.Length() > 0.0f)
		{
			//ブレーキをかける。
			Vector3 brakeSpeed = m_parent->GetMoveSpeed();
			brakeSpeed.y = 0;
			brakeSpeed *= BRAKE_POWER;
			brakeSpeed *= -1.0f;	//風船のm_moveSpeedに減算するので-1をかける。
			m_parent->SetMoveSpeed(brakeSpeed);
			BleedAir(speedToHorizontal.Length() * BRAKE_POWER);	//ブレーキのデメリットとして空気が抜ける
		}
		else
		{
			//止まっているときにBボタンを押すと、膨む。
			AddAir(1.0f);
		}
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
		BleedAir(LStickTilt.Length() * 0.05f);

		//Aボタンが押されたら、空気バースト！空気を噴射して一気に加速。
		//処理の内容間違えた。直す。
		if (g_pad[0]->IsPress(enButtonA))
		{
			Vector3 boostSpeed = m_parent->GetMoveSpeed();		
			boostSpeed.y = 0.0f;

			boostSpeed.x *= 0.2f;
			boostSpeed.z *= 0.2f;

			m_parent->SetMoveSpeed(boostSpeed);

			//空気が一定量抜ける。
			BleedAir(0.5f);
		}
	}
	if (g_pad[0]->IsPress(enButtonY))
	{
		
		m_parent->SetMoveSpeed({0.0f,1.0f,0.0f});
		//空気が一定量抜ける。
		BleedAir(0.5f);
	}
}

//airの値分、風船に空気を加える
void BalloonAir::AddAir(float air)
{
	m_airVolume += air;
	if (m_airVolume > MAX_BALLOON_SIZE)	//最大サイズよりは大きくなれない。
		m_airVolume = MAX_BALLOON_SIZE;
}
//airの値分、風船の空気を抜く
void  BalloonAir::BleedAir(float air)
{
	m_airVolume -= air;
	if (m_airVolume < MIN_BALLOON_SIZE)	//最小サイズよりは小さくなれない。
		m_airVolume = MIN_BALLOON_SIZE;
}