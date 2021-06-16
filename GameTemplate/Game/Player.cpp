#include "stdafx.h"
#include "Player.h"
#include "GameScene.h"
Player::~Player()
{
	DeleteGO(m_skinModelRender);
	DeleteGO(m_enemy[3]);
}
bool Player::Start()
{
	m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->Init("Assets/modelData/unityChan.tkm");
	if (GetPlayerNum() == 0) {
		m_skinModelRender->Init("Assets/modelData/Balloon0.tkm");		
	}
	else if (GetPlayerNum() == 1) {
		m_skinModelRender->Init("Assets/modelData/Balloon1.tkm");
	}
	else if (GetPlayerNum() == 2) {
		m_skinModelRender->Init("Assets/modelData/Balloon2.tkm");
	}
	else if (GetPlayerNum() == 3) {
		m_skinModelRender->Init("Assets/modelData/Balloon3.tkm");
	}
	//キャラコンの初期化
	m_charaCon.Init(30.0f, 70.0f, m_position);
	return true;
}
void Player::Update()
{	
	Move();
	HitWall();
	HitPlayer();
	Debug(GetPlayerNum());

}

Vector3 Player::Decele(Vector3 speed)//減速
{
	Vector3 speedVec = speed;
	
	if (speed.Length() > 0.0f) {		
		 return speedVec*-0.01;
	}
	else
		return Vector3::Zero;
}
void Player::Move()//移動
{	
	m_moveDir.x += g_pad[GetPlayerNum()]->GetLStickXF() * -0.5f;//ゲームパッドで入力した値を加算して入れる
	m_moveDir.z += g_pad[GetPlayerNum()]->GetLStickYF() * -0.5f;

	m_moveDir += Decele(m_moveDir);//MoveDirの小さくした逆ベクトルを代入する(減速処理)
	m_position = m_charaCon.Execute(m_moveDir, 1.0f);
	if (m_charaCon.IsOnGround() == false) {
		m_moveDir.y -= 1;
	}
	if (m_moveDir.y < -50) {
		m_moveDir = (m_iniPos-m_position);
		m_position = m_charaCon.Execute(m_moveDir, 1.0f);
		
		m_moveDir = { Vector3::Zero };
	}
	
	//m_position += m_moveDir;//ゲームパッドで入力した値と減速処理の値を加算合計する	
	
	SetPosition(m_position);//位置を設定する
}

void Player::HitWall()//壁にあたったとき
{	
	//Xベクトルの向きを逆にして反射したように見せる
	if (m_skinModelRender->GetPositionX() >= STAGE_WIDTH&& m_skinModelRender->GetPositionZ() <= STAGE_HOLE && m_skinModelRender->GetPositionZ() >= -STAGE_HOLE)//右の壁にあたったとき
	{}
	else if (m_skinModelRender->GetPositionX() >= STAGE_WIDTH) {
		m_position.x = STAGE_WIDTH;
		m_moveDir.x *= -1;
	}
	if (m_skinModelRender->GetPositionX() <= -STAGE_WIDTH && m_skinModelRender->GetPositionZ() <= STAGE_HOLE && m_skinModelRender->GetPositionZ() >= -STAGE_HOLE)//左の壁にあたったとき
	{}			
	else if (m_skinModelRender->GetPositionX() <= -STAGE_WIDTH) {
		m_position.x = -STAGE_WIDTH;
		m_moveDir.x *= -1;
	}
	//Zベクトルの向きを逆にして反射したように見せる
	if (m_skinModelRender->GetPositionZ() >= STAGE_DEPTH && m_skinModelRender->GetPositionX() <= STAGE_HOLE && m_skinModelRender->GetPositionX() >= -STAGE_HOLE)//
	{
		
	}
	else if (m_skinModelRender->GetPositionZ() >= STAGE_DEPTH)//奥の壁にあたったとき
	{
		m_position.z = STAGE_DEPTH;		
		m_moveDir.z *= -1;
	}
	if (m_skinModelRender->GetPositionZ() <= -STAGE_DEPTH && m_skinModelRender->GetPositionX() <= STAGE_HOLE && m_skinModelRender->GetPositionX() >= -STAGE_HOLE)//
	{
	}
	else if (m_skinModelRender->GetPositionZ() <= -STAGE_DEPTH)//手前の壁にあたったとき
	{
		m_position.z = -STAGE_DEPTH;		
		m_moveDir.z *= -1;
	}	
}

void Player::HitPlayer()
{	
	for (int i = 0; i < 3; i++)
	{
		Vector3 diff = GetPosition() - m_enemy[i]->GetPosition();//敵との距離を測る		
		if (diff.Length() < 70) {//距離が近ければ
			Vector3 tmp = GetMoveDir();			//相手と自分のベクトルを交換する
			ResetMoveDir(m_enemy[i]->GetMoveDir());
			m_enemy[i]->ResetMoveDir(tmp);
		}		
	}	
}
void Player::Debug(int pNum)//デバッグ用
{
	if (pNum == 0) {
		m_PosX_font->SetPosition({ -500,100 });
		m_PosY_font->SetPosition({ -500,50 });
		m_PosZ_font->SetPosition({ -500,0 });
	}
	else if(pNum==1){
		m_PosX_font->SetPosition({ 500,100 });
		m_PosZ_font->SetPosition({ 500,0 });
	}
	m_PosX_font->SetText(std::to_wstring(int(m_skinModelRender->GetPositionX())));
	m_PosY_font->SetText(std::to_wstring(int(m_skinModelRender->GetPositionY())));
	m_PosZ_font->SetText(std::to_wstring(int(m_skinModelRender->GetPositionZ())));
	if (g_pad[0]->IsPress(enButtonA)) {
		m_skinModelRender->SetPositionX(0);
		m_skinModelRender->SetPositionZ(0);
	}
}