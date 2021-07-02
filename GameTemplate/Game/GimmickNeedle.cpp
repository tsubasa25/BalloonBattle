#include "stdafx.h"
#include "GimmickNeedle.h"
#include "Player.h"

bool GimmickNeedle::Start()
{
	//�j�ƁA�j�̔�\��
	m_needleModelRender = NewGO<SkinModelRender>(0);
	m_needleModelRender->Init("Assets/modelData/Needle.tkm");
	m_needleBoardModelRender = NewGO<SkinModelRender>(0);
	m_needleBoardModelRender->Init("Assets/modelData/NeedleBoard.tkm");

	//�j�́A��艺�̈ʒu�ň�������ł���B
	m_needlePos = { m_needleBoardPos.x, m_needleBoardPos.y - 200.0f, m_needleBoardPos.z };

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
			m_diff = player->GetPosition() - m_needleBoardPos;//�v���C���[�Ɛj�̈ʒu�̋������Ƃ�

			//�v���C���[���j�͈̔͂ɓ����Ă�����A���ʁB
			if (fabsf(m_diff.x) < 200.0f
				&& fabsf(m_diff.z) < 200.0f)
			{
				player->PlayerDeath();
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
			if (m_needlePos.y < m_needleBoardPos.y - 200.0f)
				m_needlePos.y = m_needleBoardPos.y - 200.0f;

			m_needleModelRender->SetPosition(m_needlePos);
		}
	}
}