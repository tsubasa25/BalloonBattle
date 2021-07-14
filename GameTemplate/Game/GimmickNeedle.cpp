#include "stdafx.h"
#include "GimmickNeedle.h"
#include "Player.h"

GimmickNeedle::~GimmickNeedle()
{
	DeleteGO(m_needleModelRender);
	DeleteGO(m_needleBoardModelRender);
}

bool GimmickNeedle::Start()
{
	//針と、針の板を表示
	m_needleModelRender = NewGO<SkinModelRender>(0);
	m_needleModelRender->Init("Assets/modelData/Needle.tkm");
	m_needleBoardModelRender = NewGO<SkinModelRender>(0);
	m_needleBoardModelRender->Init("Assets/modelData/NeedleBoard.tkm");

	m_needleBoardModelRender->SetShadowCasterFlag(false);
	//針は、板より下の位置で引っ込んでいる。
	m_needlePos = { m_needleBoardPos.x, m_needleBoardPos.y - NEEDLE_HEIGHT, m_needleBoardPos.z };

	m_needleModelRender->SetPosition(m_needlePos);
	m_needleBoardModelRender->SetPosition(m_needleBoardPos);

	return true;
}

void GimmickNeedle::Update()
{
	m_needleMoveTimer++;
	Move();

	if (m_isNeedleUp == false)
	{
		//針が引っ込んでいる状態のインターバルを超えたら、針が突き出す。
		if (m_needleMoveTimer >= NEEDLE_DOWN_INTERVAL)
		{
			m_isNeedleUp = true;
			m_needleMoveTimer = 0;
		}
	}
	else
	{
		//プレイヤーを探す
		QueryGOs<Player>("player", [this](Player* player)->bool {
			//プレイヤーと針の位置の距離をとる
			Vector3 plPos = player->GetPosition();
			/*m_diff.x = plPos.x - m_needleBoardPos.x;
			m_diff.z = plPos.z - m_needleBoardPos.z;*/
			m_diff = plPos - m_needleBoardPos;
			if (player->GetCanMove() == true)
			{
				//プレイヤーが針の範囲に入っていたら、死ぬ。
				if (fabsf(m_diff.x) < NEEDLE_BOARD_HALF_SCALE
					&& fabsf(m_diff.z) < NEEDLE_BOARD_HALF_SCALE
					&& m_needlePos.y + NEEDLE_HEIGHT > plPos.y	//プレイヤーの位置が針の高さより低いかどうか
					)
				{
					player->BreakBalloon();
					player->PlayerDeath();
					SoundSource* ss = NewGO<SoundSource>(0);
					ss->Init(L"Assets/sound/風船の割れる音.wav");
					ss->Play(false);
				}
			}

			return true;
			});

		//針が突き出ている状態のインターバルを超えたら、針が引っ込む。
		if (m_needleMoveTimer > NEEDLE_UP_INTERVAL)
		{
			m_isNeedleUp = false;
			m_needleMoveTimer = 0;
		}
	}
}

//針の動きを設定
void GimmickNeedle::Move()
{
	if (m_isNeedleUp == true)
	{
		//NEEDLE_UP_INTERVALの最初の10フレームの動き(針が突き出る)
		if (m_needleMoveTimer < NEEDLE_UP_INTERVAL - (NEEDLE_UP_INTERVAL - 10))
		{
			m_needlePos.y += 20.0f;
			if (m_needlePos.y > m_needleBoardPos.y)
				m_needlePos.y = m_needleBoardPos.y;

			m_needleModelRender->SetPosition(m_needlePos);
		}
		//NEEDLE_UP_INTERVALの最後の10フレームの動き(針が引っ込む)
		else if (m_needleMoveTimer > NEEDLE_UP_INTERVAL - 10)
		{
			m_needlePos.y -= 20.0f;
			if (m_needlePos.y < m_needleBoardPos.y - NEEDLE_HEIGHT)
				m_needlePos.y = m_needleBoardPos.y - NEEDLE_HEIGHT;

			m_needleModelRender->SetPosition(m_needlePos);
		}
	}
}