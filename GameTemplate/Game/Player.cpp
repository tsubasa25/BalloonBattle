#include "stdafx.h"
#include "Player.h"
Player::~Player()
{

}
bool Player::Start()
{
	m_player = NewGO<SkinModelRender>(0);
	if (GetPlayerNum() == 0) {
		m_player->Init("Assets/modelData/Ballon.tkm");
	}
	else if (GetPlayerNum() == 1) {
		m_player->Init("Assets/modelData/Ballon2.tkm");
	}
	
	return true;
}
void Player::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		int a = 0;
		a++;
	}
	
	if (GetPlayerNum() == 0) {
		position.x -= g_pad[0]->GetRStickXF() * 0.5;
		position.z -= g_pad[0]->GetRStickYF() * 0.2;
	}
	else if (GetPlayerNum() == 1) {
		position.x -= g_pad[1]->GetRStickXF() * 0.2;
		position.z -= g_pad[1]->GetRStickYF() * 0.2;
	}	
	LightPos += position;
	m_player->SetPosition(LightPos);
}