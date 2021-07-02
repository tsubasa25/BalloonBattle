#include "stdafx.h"
#include "Player.h"
#include "GameScene.h"
#include "BackGround.h"
#include "UIDisplay.h"
Player::~Player()
{
	DeleteGO(m_skinModelRender);
	DeleteGO(m_PosX_font);
	DeleteGO(m_PosY_font);
	DeleteGO(m_PosZ_font);
	DeleteGO(m_Size_font);
	DeleteGO(pointLight);
	if (m_IsArrowOn) {
		DeleteGO(m_skinModelRenderArrow);
	}
	GameScene* gameScene = FindGO<GameScene>("gameScene");
	gameScene->SetIsAlive(m_playerNum, false);
	gameScene->SetPlayerCount(gameScene->GetPlayerCount() - 1);
	
	DeleteGO(m_myAir);
}
bool Player::Start()
{
	//デバッグ用
	m_skinModelRenderArrow = NewGO<SkinModelRender>(0);
	m_skinModelRenderArrow->Init("Assets/modelData/arrow.tkm");

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
	else if (GetPlayerNum() == 4) {
		m_skinModelRender->Init("Assets/modelData/Balloon4.tkm");
	}
	else if (GetPlayerNum() == 5) {
		m_skinModelRender->Init("Assets/modelData/Balloon5.tkm");
	}
	else if (GetPlayerNum() == 6) {
		m_skinModelRender->Init("Assets/modelData/Balloon6.tkm");
	}
	else if (GetPlayerNum() == 7) {
		m_skinModelRender->Init("Assets/modelData/Balloon7.tkm");
	}

	m_myAir = NewGO<BalloonAir>(0);
	m_myAir->SetParent(this);
	m_myAir->SetParentNum(m_playerNum);

	m_myAir->SetAirVolume(m_myAirVolume);	//空気の量の初期値を設定

	m_backGround = FindGO<BackGround>("backGround");
	m_UIDisplay = FindGO<UIDisplay>("UIdisplay");

	//キャラコンの初期化
	m_charaCon.Init((m_myAirVolume/2), m_position);

	//m_charaCon.Init(100, m_bulloonSize, m_position);
	pointLight->SetColor(POINTLIGHT_COLOR);
	pointLight->SetRange(POINTLIGHT_RANGE);
	pointLight->SetPosition({ m_position });

	return true;
}
void Player::Update()
{
	Move();
	Tilt();
	HitWall();
	HitPlayer();
	Debug(GetPlayerNum());
	SetScale({ m_myAirVolume / BALLOON_SIZE_BASE,m_myAirVolume / BALLOON_SIZE_BASE,m_myAirVolume / BALLOON_SIZE_BASE, });
	m_charaCon.ReInit((m_myAirVolume / 2), m_position);	
}

Vector3 Player::Decele(Vector3 speed)//減速
{
	Vector3 speedVec = speed;
	
	if (speed.Length() > 0.0f) {		
		//return speedVec*-0.02;
		return speedVec * -m_myAirVolume/2 / DESELE_VOLUME;
	}
	else {
		return Vector3::Zero;
	}
}
void Player::Move()//移動
{	
	m_moveSpeed.x += g_pad[GetPlayerNum()]->GetLStickXF() * 0.5f;//ゲームパッドで入力した値を加算して入れる
	m_moveSpeed.z += g_pad[GetPlayerNum()]->GetLStickYF() * 0.5f;
	
	m_moveSpeed += Decele(m_moveSpeed);//MoveDirの小さくした逆ベクトルを代入する(減速処理)
	m_position = m_charaCon.Execute(m_moveSpeed, 1.0f);//ポジションを決定
	if (m_charaCon.IsOnGround() == false) {//地面についていなかったら
		m_moveSpeed.y -= pow( GRAVITY_SPEED,GRAVITY_INDEX );//重力を与える
	}
	else {
		m_moveSpeed.y = 0;
	}
	if (m_position.y < OVER_STAGE_LINE.y	//ステージから落ちるか、
		|| fabsf(m_position.x) > OVER_STAGE_LINE.x
		|| fabsf(m_position.z) > OVER_STAGE_LINE.z	//ステージから大きく離れたら。
		) {
		PlayerDeath();
	}

	//ほどんど動いていないとき、移動速度を0にする。
	if (fabsf(m_moveSpeed.x) < 0.1f && fabsf(m_moveSpeed.z) < 0.1f)
	{
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;
	}
	
	SetPosition(m_position);//位置を設定する
	pointLight->SetPosition({ m_position });
}

void Player::HitWall()//壁にあたったとき
{			
	if (m_charaCon.GetIsHitWall() == true) {
		m_moveSpeed = ReboundSpeed();
	}
}

void Player::HitPlayer()
{
	for (int i = 0; i < m_enemy.size(); i++)		//どの敵にあたったか探す
	{
		Vector3 diff = GetPosition() - m_enemy[i]->GetPosition();//敵との距離を測る
		if (diff.Length() < (m_myAirVolume /2+m_enemy[i]->m_myAirVolume /2)+1) {//コリジョンより少し広い範囲にきたらあたったとみなす
			//diff.y = 0;									//高さを無視する
			//m_hitLoopCount = 0;
			Vector3 tmp = m_enemy[i]->GetMoveSpeed();//敵の勢いを保存する
			diff.Normalize();//敵との向きをとる
			//大きさに比例してふっとばしやすくなる
			m_enemy[i]->m_moveSpeed = (diff*GetMoveSpeed().Length() * -(m_myAirVolume/ (INI_AIR_VOLUME/ REBOUND_POWER)));//相手に自分の勢いを渡す
			m_moveSpeed = diff*(tmp.Length() * ((INI_AIR_VOLUME) /m_myAirVolume));//自分は大きさに反比例してふっとばされやすくなる
		
			m_myAir->BleedAir(m_myAirVolume * 0.1f);
		}		
	}
}

Vector3 Player::ReboundSpeed()//モデルの法線から反射する方向を求めて移動方向を決定する
{
	//壁の法線の外積を取る
	Vector3 wallNormal = m_charaCon.GetWallNormal();//あたった壁の法線を受け取る

	Vector3 hitNormalCross = Vector3::Zero;
	hitNormalCross.Cross(Vector3::AxisY, wallNormal);//壁の法線の外積を求める

	hitNormalCross.Normalize();//正規化する

	Vector3 Dir = m_moveSpeed;
	Dir.Normalize();
	//法線の外積と進行方向の内積を取る
	float naisei = hitNormalCross.Dot(Dir);

	Quaternion rot;
	rot.SetRotation(Vector3::AxisY, naisei * 2);//外積と進行方向の角度の差を二倍した分
	rot.Apply(Dir);//進行方向を回転させる

	return Dir * -m_moveSpeed.Length();//進行方向に反射する前の勢いをかける
}
void Player::Debug(int pNum)//デバッグ用
{
	if (pNum == 0) {
		m_PosX_font->SetPosition({ -500,100 });
		m_PosY_font->SetPosition({ -500,50 });
		m_PosZ_font->SetPosition({ -500,0 });
		m_Size_font->SetPosition({ -500,-50 });
	}
	else if(pNum==1){
		m_PosX_font->SetPosition({ 500,100 });
		m_PosZ_font->SetPosition({ 500,0 });
	}
	m_PosX_font->SetText(std::to_wstring(int(m_skinModelRender->GetPositionX())));
	m_PosY_font->SetText(std::to_wstring(int(m_skinModelRender->GetPositionY())));
	m_PosZ_font->SetText(std::to_wstring(int(m_skinModelRender->GetPositionZ())));
	m_Size_font->SetText(std::to_wstring(int(m_myAirVolume)));	
	if (g_pad[pNum]->IsPress(enButtonLB1)) {
			m_myAirVolume += 1;
			//m_charaCon.ReInit((m_myAirVolume / 2), m_position);

			//m_charaCon.ReInit((m_myAirVolume / 2),m_position);
			//m_moveSpeed.y = 0;
	}
	if (g_pad[pNum]->IsPress(enButtonRB1)) {
			m_myAirVolume -= 1;
			Vector3 Accele = m_moveSpeed;
			Accele.Normalize();
			m_moveSpeed += Accele;
			//m_charaCon.ReInit((m_myAirVolume / 2),m_position);
	}
	
	
	if (m_playerCount >= 2) {//プレイヤーが二人以上なら
		if (m_IsAIOn) {
			if (m_playerNum == 0) {//敵が自分めがけて突進してくる
				Vector3 diff = Vector3::Zero;
				diff = m_position - m_enemy[0]->m_position;
				diff.Normalize();
				m_enemy[0]->m_moveSpeed += diff * 0.3f;
				if (m_stock != m_oldStock) {
					m_oldStock--;
					m_enemy[0]->m_moveSpeed = (m_enemy[0]->m_iniPos - m_enemy[0]->m_position);//初期座標にとばす
					m_enemy[0]->m_position = m_enemy[0]->m_charaCon.Execute(m_enemy[0]->m_moveSpeed, 1.0f);

					m_enemy[0]->m_moveSpeed = { Vector3::Zero };//スピードをゼロにする
				}
			}
		}
	}
	if (m_IsArrowOn) {//矢印を表示するかどうか
		//移動ベクトルを可視化する
		Vector3 Dir = m_moveSpeed;
		Dir.y = 0;
		Dir.Normalize();//大きさを位置にする
		float x = Dir.Dot(Vector3::AxisX);//X軸から何度ずれているかを入れる
		Dir.z *= -1;
		float angleX = acosf(x);//アークコサイン
		if (Dir.z < 0) {
			angleX *= -1;
		}
		angleX -= 0.5 * PAI;

		m_rot.SetRotationY(angleX);//ｘ度だけY軸を回す
		m_skinModelRenderArrow->SetRotation(m_rot);//角度を設定する

		m_skinModelRenderArrow->SetPosition(m_position);

		m_arrowSize.x = m_arrowSize.z = m_moveSpeed.Length() / 3;
		m_skinModelRenderArrow->SetScale(m_arrowSize);
	}
}

void Player::Tilt()
{
	Vector3 dir = m_moveSpeed;
	dir.y = 0.0f;
	dir.Normalize();

	float tiltPower = m_moveSpeed.Length() * 0.02f;

	Vector3 right = Cross(Vector3::AxisY, dir);
	
	m_playerRot.SetRotation(right, tiltPower);

	m_playerRot.Apply(dir);

	m_skinModelRender->SetRotation(m_playerRot);

}

//プレイヤーが死亡したときの処理
void Player::PlayerDeath()
{
	m_stock--;//ストックを減らす
	m_UIDisplay->SetPlayerDecStock(m_playerNum);//UIにストックが減ったことを伝える
	if (m_stock > 0) {//ストックが残っていたら
		m_resPos = m_backGround->GetRespawnPosition(m_playerNum);
		m_moveSpeed = { Vector3::Zero };//スピードをゼロにする
		m_charaCon.SetPosition(m_resPos);	//キャラコンに座標を設定
		SetPosition(m_resPos);	//初期座標に飛ばす。
		
		m_myAirVolume = INI_AIR_VOLUME;
		m_myAir->SetAirVolume(INI_AIR_VOLUME);
	}
	else {			
			m_UIDisplay->SetPlayerDeath(m_playerNum);//UIに死亡したことを伝える			
		
		for (int i = 0; i < m_enemy.size();i++) {
			it = std::find(
				m_enemy[i]->m_enemy.begin(),
				m_enemy[i]->m_enemy.end(),
				this
			);
			if (it != m_enemy[i]->m_enemy.end()) {
				//見つかったので削除
				m_enemy[i]->m_enemy.erase(it);
			}
		}
		DeleteGO(this);
	}
}