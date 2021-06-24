#include "stdafx.h"
#include "Player.h"
#include "GameScene.h"
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
	//キャラコンの初期化
	m_charaCon.Init((m_balloonSize/2) , m_balloonSize, m_position);
	//m_charaCon.Init(100, m_bulloonSize, m_position);
	pointLight->SetColor({ 10,10,10 });
	pointLight->SetRange(200);
	pointLight->SetPosition({ m_position });
	return true;
}
void Player::Update()
{
	Move();
	HitWall();
	//HitPlayer();
	Air();
	Debug(GetPlayerNum());
	SetScale({ m_balloonSize / INI_BALLOON_SIZE,m_balloonSize / INI_BALLOON_SIZE,m_balloonSize / INI_BALLOON_SIZE, });	
}

Vector3 Player::Decele(Vector3 speed)//減速
{
	Vector3 speedVec = speed;
	
	if (speed.Length() > 0.0f) {		
		 //return speedVec*-0.02;
		return speedVec * -m_balloonSize / 3500;
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
		m_moveSpeed.y -= pow(0.7f, 2.0f);//重力を与える
	}
	else {
		m_moveSpeed.y = 0;
	}
	if (m_position.y < -1000) {//ステージから落ちたら
		m_stock--;//ストックを減らす
		if (m_stock > 0) {//ストックが残っていたら
			m_moveSpeed = (m_iniPos - m_position);//初期座標にとばす
			m_position = m_charaCon.Execute(m_moveSpeed, 1.0f);
			
			m_moveSpeed = { Vector3::Zero };//スピードをゼロにする
		}
		else {
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
		HitPlayer();
		if (m_enemyHit == false) {//敵ではなく壁にあっていれば
			//空気が抜ける
			//BleedAir(m_moveSpeed.Length());

			//反射する方向を求める
			m_moveSpeed = ReboundSpeed();
		}
	}
}

void Player::HitPlayer()
{
	for (int i = 0; i < m_enemy.size(); i++)		//どの敵にあたったか探す
	{
		Vector3 diff = GetPosition() - m_enemy[i]->GetPosition();//敵との距離を測る
		diff.y = 0;									//高さを無視する
		//if (diff.Length() < (m_bulloonSize/2+m_enemy[i]->m_bulloonSize/2)+1) {//コリジョンがUpdateできたらこっち
		if (diff.Length() < (INI_BALLOON_SIZE+2)){//距離が近ければ
			m_enemyHit = true;						//敵とあたったとみなす
			Vector3 tmp = m_enemy[i]->GetMoveSpeed();//敵の勢いを保存する
			//大きさに比例してふっとばしやすくなる
			m_enemy[i]->m_moveSpeed = (ReboundSpeed() * -(m_balloonSize/ (INI_BALLOON_SIZE/ REBOUND_POWER)));//相手に自分の勢いを渡す
			
			if (m_moveSpeed.Length() < m_enemy[i]->m_balloonSize / MASS_DIVISOR) {//自分の勢いより、相手の質量が大きければ跳ね返される
				m_enemy[i]->m_moveSpeed = (ReboundSpeed() * -(m_balloonSize / (INI_BALLOON_SIZE * REBOUND_POWER)));//敵はすこし押される
				m_moveSpeed = ReboundSpeed();//自分は跳ね返される				
			}
			else {				
				m_moveSpeed = tmp * ((INI_BALLOON_SIZE* REBOUND_POWER) /m_balloonSize);//自分は大きさに反比例してふっとばされやすくなる
			}
			//BleedAir(m_moveSpeed.Length());	//自分の空気が抜ける
			//m_enemy[i]->BleedAir(m_moveSpeed.Length());//相手の空気も抜ける。
		}	
		else {//敵との距離が遠ければなにもしない
			m_enemyHit = false;						//敵と合っていない
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
	m_Size_font->SetText(std::to_wstring(int(m_balloonSize)));	
	if (g_pad[pNum]->IsPress(enButtonLB1)) {
			m_balloonSize += 1;			
			//m_charaCon.ReInit((m_bulloonSize / 2), 70,m_position);
			//m_moveSpeed.y = 0;
	}
	if (g_pad[pNum]->IsPress(enButtonRB1)) {
			m_balloonSize -= 1;			
			Vector3 Accele = m_moveSpeed;
			Accele.Normalize();
			m_moveSpeed += Accele;
			//m_charaCon.ReInit((m_bulloonSize / 2), 70,m_position);
	}
	
	
	if (m_playerCount >= 2) {//プレイヤーが二人以上なら
		if (m_IsAIOn) {
			if (m_playerNum == 0) {//敵が自分めがけて突進してくる
				Vector3 diff = Vector3::Zero;
				diff = m_position - m_enemy[0]->m_position;
				diff.Normalize();
				m_enemy[0]->m_moveSpeed += diff * 0.3;
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
		angleX -= 0.5 * 3.14159;

		m_rot.SetRotationY(angleX);//ｘ度だけY軸を回す
		m_skinModelRenderArrow->SetRotation(m_rot);//角度を設定する

		m_skinModelRenderArrow->SetPosition(m_position);

		m_arrowSize.x = m_arrowSize.z = m_moveSpeed.Length() / 3;
		m_skinModelRenderArrow->SetScale(m_arrowSize);
	}
}

//風船の空気関係
void Player::Air()
{
	Vector3 speedToHorizontal = m_moveSpeed;	//水平方向へのスピード(y方向は0)
	speedToHorizontal.y = 0;

	//ブレーキと空気注入の処理
	if (g_pad[GetPlayerNum()]->IsPress(enButtonB))
	{
		if (speedToHorizontal.Length() > 0.0f)
		{
			//ブレーキをかける。
			m_moveSpeed.x -= m_moveSpeed.x * BRAKE_POWER;
			m_moveSpeed.z -= m_moveSpeed.z * BRAKE_POWER;
			BleedAir(speedToHorizontal.Length() * BRAKE_POWER);	//ブレーキのデメリットとして空気が抜ける
		}
		else
		{
			//サイズを大きくする。
			AddAir(1.0f);
		}
	}
	
	//プレイヤーがスティックを倒しているとき
	if (g_pad[GetPlayerNum()]->GetLStickXF() != 0.0f
		|| g_pad[GetPlayerNum()]->GetLStickYF() != 0.0f)
	{
		//Lスティックの傾きの大きさに応じて、空気が抜ける。
		Vector3 LStickTilt = {
			(g_pad[GetPlayerNum()]->GetLStickXF()),
			(g_pad[GetPlayerNum()]->GetLStickYF()),
			0.0f
		};
		BleedAir(LStickTilt.Length() * 0.05f);

		//Aボタンが押されたら、空気バースト！空気を噴射して一気に加速。
		//処理の内容間違えた。直す。
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			Vector3 boostDir;
			boostDir.x = g_pad[GetPlayerNum()]->GetLStickXF();
			boostDir.z = g_pad[GetPlayerNum()]->GetLStickYF();
			boostDir.y = 0.0f;
			boostDir.Normalize();

			boostDir.x *= 70.0f;
			boostDir.z *= 70.0f;

			m_moveSpeed.x = boostDir.x;
			m_moveSpeed.z = boostDir.z;

			//空気が一定量抜ける。
			BleedAir(20.0f);
		}
	}
	if (g_pad[0]->IsTrigger(enButtonY))
	{
		m_moveSpeed.y = 30.0f;
		//空気が一定量抜ける。
		BleedAir(20.0f);
	}
}

//airの値分、風船に空気を加える
void Player::AddAir(float air)
{ 
	m_balloonSize += air;
	if (m_balloonSize > MAX_BALLOON_SIZE)	//最大サイズよりは大きくなれない。
		m_balloonSize = MAX_BALLOON_SIZE;
}
//airの値分、風船の空気を抜く
void  Player::BleedAir(float air)			
{ 
	m_balloonSize -= air; 
	if (m_balloonSize < MIN_BALLOON_SIZE)	//最小サイズよりは小さくなれない。
		m_balloonSize = MIN_BALLOON_SIZE;
}