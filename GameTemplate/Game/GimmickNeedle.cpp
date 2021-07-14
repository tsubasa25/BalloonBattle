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
	//�j�ƁA�j�̔�\��
	m_needleModelRender = NewGO<SkinModelRender>(0);
	m_needleModelRender->Init("Assets/modelData/Needle.tkm");
	m_needleBoardModelRender = NewGO<SkinModelRender>(0);
	m_needleBoardModelRender->Init("Assets/modelData/NeedleBoard.tkm");

	m_needleBoardModelRender->SetShadowCasterFlag(false);
	//�j�́A��艺�̈ʒu�ň�������ł���B
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
		//�j����������ł����Ԃ̃C���^�[�o���𒴂�����A�j���˂��o���B
		if (m_needleMoveTimer >= NEEDLE_DOWN_INTERVAL)
		{
			m_isNeedleUp = true;
			m_needleMoveTimer = 0;
		}
	}
	else
	{
		//�v���C���[��T��
		QueryGOs<Player>("player", [this](Player* player)->bool {
			//�v���C���[�Ɛj�̈ʒu�̋������Ƃ�
			Vector3 plPos = player->GetPosition();
			/*m_diff.x = plPos.x - m_needleBoardPos.x;
			m_diff.z = plPos.z - m_needleBoardPos.z;*/
			m_diff = plPos - m_needleBoardPos;
			if (player->GetCanMove() == true)
			{
				//�v���C���[���j�͈̔͂ɓ����Ă�����A���ʁB
				if (fabsf(m_diff.x) < NEEDLE_BOARD_HALF_SCALE
					&& fabsf(m_diff.z) < NEEDLE_BOARD_HALF_SCALE
					&& m_needlePos.y + NEEDLE_HEIGHT > plPos.y	//�v���C���[�̈ʒu���j�̍������Ⴂ���ǂ���
					)
				{
					player->BreakBalloon();
					player->PlayerDeath();
					SoundSource* ss = NewGO<SoundSource>(0);
					ss->Init(L"Assets/sound/���D�̊���鉹.wav");
					ss->Play(false);
				}
			}

			return true;
			});

		//�j���˂��o�Ă����Ԃ̃C���^�[�o���𒴂�����A�j���������ށB
		if (m_needleMoveTimer > NEEDLE_UP_INTERVAL)
		{
			m_isNeedleUp = false;
			m_needleMoveTimer = 0;
		}
	}
}

//�j�̓�����ݒ�
void GimmickNeedle::Move()
{
	if (m_isNeedleUp == true)
	{
		//NEEDLE_UP_INTERVAL�̍ŏ���10�t���[���̓���(�j���˂��o��)
		if (m_needleMoveTimer < NEEDLE_UP_INTERVAL - (NEEDLE_UP_INTERVAL - 10))
		{
			m_needlePos.y += 20.0f;
			if (m_needlePos.y > m_needleBoardPos.y)
				m_needlePos.y = m_needleBoardPos.y;

			m_needleModelRender->SetPosition(m_needlePos);
		}
		//NEEDLE_UP_INTERVAL�̍Ō��10�t���[���̓���(�j����������)
		else if (m_needleMoveTimer > NEEDLE_UP_INTERVAL - 10)
		{
			m_needlePos.y -= 20.0f;
			if (m_needlePos.y < m_needleBoardPos.y - NEEDLE_HEIGHT)
				m_needlePos.y = m_needleBoardPos.y - NEEDLE_HEIGHT;

			m_needleModelRender->SetPosition(m_needlePos);
		}
	}
}