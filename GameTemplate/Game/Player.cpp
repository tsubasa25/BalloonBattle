#include "stdafx.h"
#include "Player.h"
#include "GameScene.h"
#include "BackGround.h"
#include "UIDisplay.h"
#include "ResultScene.h"
#include "BalloonAir.h"

namespace nsBalloon {
	Player::~Player()
	{
		DeleteGO(m_skinModelRender);

		if (m_isArrowOn) {
			DeleteGO(m_skinModelRenderArrow);
		}
		DeleteGO(m_myAir);
	}
	bool Player::Start()
	{
		//デバッグ用
		m_skinModelRenderArrow = NewGO<SkinModelRender>(0);
		m_skinModelRenderArrow->SetShadowCasterFlag(false);

		m_skinModelRenderArrow->Init("Assets/modelData/arrow.tkm");
		m_skinModelRenderArrow->SetScale({ Vector3::Zero });

		m_skinModelRender = NewGO<SkinModelRender>(0);
		m_skinModelRender->SetShadowCasterFlag(true);

		//m_skinModelRender->Init("Assets/modelData/Balloon0.tkm");
		char filePath[256];
		sprintf(filePath, "Assets/modelData/Balloon%d.tkm", GetPlayerNum());
		m_skinModelRender->Init(filePath);//風船をそれぞれの色にする

		m_myAir = NewGO<BalloonAir>(0, "balloonAir");
		m_myAir->SetParent(this);
		m_myAir->SetParentNum(m_playerNum);

		m_myAir->SetAirVolume(m_myAirVolume);	//空気の量の初期値を設定

		m_backGround = FindGO<BackGround>("backGround");
		m_UIDisplay = FindGO<UIDisplay>("UIdisplay");
		m_gameScene = FindGO<GameScene>("gameScene");

		//キャラコンの初期化
		m_charaCon.Init((m_myAirVolume / 2), m_position);

		//todo char16_t版のsprntfを利用して。 
		//16_t版がない！？
		if (GetPlayerNum() == 0) {
			m_breakEff.Init(u"Assets/effect/BalloonBreak00.efk");
			m_plColor = { Vector4::Red };
		}
		else if (GetPlayerNum() == 1) {
			m_breakEff.Init(u"Assets/effect/BalloonBreak01.efk");
			m_plColor = { Vector4::Blue };
		}
		else if (GetPlayerNum() == 2) {
			m_breakEff.Init(u"Assets/effect/BalloonBreak02.efk");
			m_plColor = { Vector4::Green };
		}
		else if (GetPlayerNum() == 3) {
			m_breakEff.Init(u"Assets/effect/BalloonBreak03.efk");
			m_plColor = { Vector4::Yellow };
		}
		else if (GetPlayerNum() == 4) {
			m_breakEff.Init(u"Assets/effect/BalloonBreak04.efk");
			m_plColor = { Vector4::Orange };
		}
		else if (GetPlayerNum() == 5) {
			m_breakEff.Init(u"Assets/effect/BalloonBreak05.efk");
			m_plColor = { Vector4::Pink };
		}
		else if (GetPlayerNum() == 6) {
			m_breakEff.Init(u"Assets/effect/BalloonBreak06.efk");
			m_plColor = { Vector4::Gray };
		}
		else if (GetPlayerNum() == 7) {
			m_breakEff.Init(u"Assets/effect/BalloonBreak07.efk");
			m_plColor = { Vector4::Purple };
		}

		SetPosition(m_position);//位置を設定する
		SetScale({ m_myAirVolume / nsPlConstant::BALLOON_SIZE_BASE,m_myAirVolume / nsPlConstant::BALLOON_SIZE_BASE,m_myAirVolume / nsPlConstant::BALLOON_SIZE_BASE, });

		m_hitEff.Init(u"Assets/effect/HitEff.efk");

		return true;
	}
	void Player::Update()
	{
		if (m_canMove == false)
		{
			if (m_respawnFlag == true)
			{
				Respawn();
			}
			return;
		}
		Move();
		Tilt();
		HitWall();
		HitPlayer();
		Debug(GetPlayerNum());
		SetScale({ m_myAirVolume / nsPlConstant::BALLOON_SIZE_BASE,m_myAirVolume / nsPlConstant::BALLOON_SIZE_BASE,m_myAirVolume / nsPlConstant::BALLOON_SIZE_BASE, });
		m_charaCon.ReInit((m_myAirVolume / 2), m_position);

		if (m_enemy.empty())
		{
			m_gameScene->SetGameState(nsGSConstant::GAME_STATE_RESULT);
			m_resultScene = NewGO<ResultScene>(0, "resultScene");
			m_resultScene->SetResultMode(m_resultScene->GetEnGameSet());
			m_resultScene->SetWinner(this);
			m_canMove = false;
		}
	}

	Vector3 Player::Decele(Vector3 speed)//減速
	{
		if (speed.LengthSq() > 0.0f) {
			float SizeCoefficient = (m_myAirVolume / nsPlConstant::INI_AIR_VOLUME);//大きさ係数			
			//return speed * -m_myAirVolume / 2 / nsPlConstant::DESELE_VOLUME;
			return (speed / nsPlConstant::DESELE_VOLUME)*-SizeCoefficient;
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
			m_moveSpeed.y -= pow(nsPlConstant::GRAVITY_SPEED, nsPlConstant::GRAVITY_INDEX);//重力を与える
		}
		else {
			m_moveSpeed.y = 0;
		}
		if (m_position.y < nsPlConstant::OVER_STAGE_LINE.y	//ステージから落ちるか、
			|| fabsf(m_position.x) > nsPlConstant::OVER_STAGE_LINE.x
			|| fabsf(m_position.z) > nsPlConstant::OVER_STAGE_LINE.z	//ステージから大きく離れたら。
			) {
			PlayerDeath();//プレイヤーを殺す
			SoundSource* ss = NewGO<SoundSource>(0);//効果音
			ss->Init(L"Assets/sound/風船が落ちて死んだ音.wav");
			ss->SetVolume(nsPlConstant::SOUND_BALLOON_SE_VOLUME);
			ss->Play(false);
		}

		//ほどんど動いていないとき、移動速度を0にする。
		if (fabsf(m_moveSpeed.x) < 0.1f && fabsf(m_moveSpeed.z) < 0.1f)
		{
			m_moveSpeed.x = 0.0f;
			m_moveSpeed.z = 0.0f;
		}

		SetPosition(m_position);//位置を設定する
		m_lightPos = m_position;
		m_lightPos.y += m_myAirVolume;
		//pointLight->SetPosition({ m_lightPos });
	}

	void Player::HitWall()//壁にあたったとき
	{
		if (m_charaCon.GetIsHitWall() == true) {
			m_moveSpeed = ReboundSpeed();

			//SEを再生
			SoundSource* ss = NewGO<SoundSource>(0);
			ss->Init(L"Assets/sound/風船の跳ねる音.wav");
			ss->SetVolume(nsPlConstant::SOUND_BALLOON_SE_VOLUME);
			ss->Play(false);
		}
	}

	void Player::HitPlayer()
	{
		for (int i = 0; i < m_enemy.size(); i++)		//どの敵にあたったか探す
		{
			Vector3 diff = GetPosition() - m_enemy[i]->GetPosition();//敵との距離を測る
			if (diff.Length() < (m_myAirVolume / 2 + m_enemy[i]->m_myAirVolume / 2) + 1) {//コリジョンより少し広い範囲にきたらあたったとみなす
				//diff.y = 0;									//高さを無視する
				//m_hitLoopCount = 0;
				Vector3 tmp = m_enemy[i]->GetMoveSpeed();//敵の勢いを保存する
				diff.Normalize();//敵との向きをとる
				//大きさに比例してふっとばしやすくなる
				m_enemy[i]->m_moveSpeed = (diff * GetMoveSpeed().Length() * -(m_myAirVolume / (nsPlConstant::INI_AIR_VOLUME / nsPlConstant::REBOUND_POWER)));//相手に自分の勢いを渡す
				m_moveSpeed = diff * (tmp.Length() * ((nsPlConstant::INI_AIR_VOLUME) / m_myAirVolume));//自分は大きさに反比例してふっとばされやすくなる

				m_myAir->BleedAir(m_myAirVolume * 0.1f);

				PlayEffHit();

				if (m_enemy[i]->GetPlayerNum() > m_playerNum)
				{
					//SEを再生
					SoundSource* ss = NewGO<SoundSource>(0);
					ss->Init(L"Assets/sound/風船の跳ねる音.wav");
					ss->SetVolume(nsPlConstant::SOUND_BALLOON_SE_VOLUME);
					ss->Play(false);
				}
				//最後にあたった敵の番号を記録する
				m_hitLastNum = i;
				m_enemy[i]->m_hitLastNum = i;
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

		Quaternion rot = Quaternion::Identity;
		rot.SetRotation(Vector3::AxisY, naisei * 2);//外積と進行方向の角度の差を二倍した分
		rot.Apply(Dir);//進行方向を回転させる

		return Dir * -m_moveSpeed.Length();//進行方向に反射する前の勢いをかける
	}
	void Player::Debug(int pNum)//デバッグ用
	{
		if (m_isAIOn) {//矢印を表示するか
			if (m_playerCount >= 2) {//プレイヤーが二人以上なら
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
		if (m_isArrowOn) {//矢印を表示するかどうか
			//移動ベクトルを可視化する
			Vector3 Dir = m_moveSpeed;
			Dir.y = 0.f;
			Dir.Normalize();//大きさを位置にする
			float x = Dir.Dot(Vector3::AxisX);//X軸から何度ずれているかを入れる
			Dir.z *= -1.f;
			float angleX = acosf(x);//アークコサイン
			if (Dir.z < 0.f) {
				angleX *= -1.f;
			}
			angleX -= 0.5f * nsPlConstant::PAI;

			m_rot.SetRotationY(angleX);//ｘ度だけY軸を回す
			m_skinModelRenderArrow->SetRotation(m_rot);//角度を設定する
			Vector3 ArrowPos = m_position;
			ArrowPos.y += 50.0f;

			m_skinModelRenderArrow->SetPosition(ArrowPos);

			m_arrowSize.x = m_arrowSize.z = m_moveSpeed.Length() / 3.0f;
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
		UIDisplay* UIdisplay = FindGO<UIDisplay>("UIdisplay");
		if (UIdisplay != nullptr)
		{
			UIdisplay->SetIsDeath(true);
			//敵が死んでDeleteGOされたときにm_enemyの順番が変わるからおかしくなるかも
			//if (m_hitLastNum < 8) {//誰にもあたってなかったら加算されない
			//	if (m_hitLastNum < m_enemy.size())
			//	{
			//		m_enemy[m_hitLastNum]->AddKillPoint();//キルポイントを加算する
			//		m_UIDisplay->SetIsMinus(m_playerNum);
			//		m_UIDisplay->SetIsPlus(m_enemy[m_hitLastNum]->GetPlayerNum());
			//		
			//	}
			//}
			UIdisplay->SetIsMinus(m_playerNum);
		}
		Effect soulEff;
		soulEff.Init(u"Assets/effect/SoulRise.efk");
		soulEff.SetPosition(m_position);
		soulEff.SetScale({ 1.0f,1.0f,1.0f });
		soulEff.Play();
		soulEff.Update();

		m_stock--;//ストックを減らす
		//m_UIDisplay->SetPlayerDecStock(m_playerNum);//UIにストックが減ったことを伝える
		m_UIDisplay->SetPlayerStock(m_stock, m_playerNum);

		m_myAir->AcceleSEStop();
		m_myAir->RiseSEStop();
		m_myAir->InflateSEStop();

		if (m_stock > 0) {//ストックが残っていたら
			m_respawnFlag = true;
			m_respawnCount = nsPlConstant::RESPAWN_INTERVAL;

			m_myAirVolume = nsPlConstant::INI_AIR_VOLUME;
			m_myAir->SetAirVolume(nsPlConstant::INI_AIR_VOLUME);

			m_canMove = false;
		}
		else {
			m_UIDisplay->SetPlayerDeath(m_playerNum);//UIに死亡したことを伝える			

			for (int i = 0; i < m_enemy.size(); i++) {
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
			m_myAir->SetAirVolume(nsPlConstant::INI_AIR_VOLUME);
			DeleteGO(this);
		}
	}

	void Player::BreakBalloon()
	{
		m_breakEff.SetPosition(m_position);
		//エフェクトのサイズを風船のサイズに合わせる。
		Vector3 size = { m_myAirVolume / nsPlConstant::BALLOON_SIZE_BASE,m_myAirVolume / nsPlConstant::BALLOON_SIZE_BASE,m_myAirVolume / nsPlConstant::BALLOON_SIZE_BASE, };
		size *= 20.0f;	//エフェクトのサイズを大きくする。
		m_breakEff.SetScale(size);
		m_breakEff.Play();
		m_breakEff.Update();
	}

	//衝突時のエフェクトを再生する
	void Player::PlayEffHit()
	{
		//エフェクトの向きを計算
		Vector3 front = m_moveSpeed;
		front.Normalize();
		float n = front.Dot(Vector3::AxisZ);
		float angle = acosf(n);
		if (front.z < 0) {
			angle *= -1;
		}
		Quaternion qRot = Quaternion::Identity;
		qRot.SetRotation(Vector3::AxisY, angle);
		m_hitEff.SetRotation(qRot);

		//エフェクトの位置を計算
		Vector3 pos = m_position;
		pos += front * 3.0f;
		pos.y += 20.0f;
		m_hitEff.SetPosition(pos);

		//エフェクトのサイズ
		m_hitEff.SetScale({ m_myAirVolume / 3,m_myAirVolume / 3,m_myAirVolume / 3 });

		m_hitEff.Play();
		m_hitEff.Update();
	}

	void Player::Respawn()
	{

		if (m_respawnCount == nsPlConstant::RESPAWN_INTERVAL)
		{
			//サイズを小さくして見えなくする。
			m_skinModelRender->SetScale({ Vector3::Zero });
			m_charaCon.ReInit(0.0f, m_position);
			m_skinModelRenderArrow->SetScale({ Vector3::Zero });
		}
		if (m_respawnCount == 1)
		{
			m_resPos = m_backGround->GetRespawnPosition(m_playerNum);
		}
		if (m_respawnCount <= 0)
		{
			m_moveSpeed = { Vector3::Zero };//スピードをゼロにする
			m_charaCon.SetPosition(m_resPos);	//キャラコンに座標を設定
			SetPosition(m_resPos);	//初期座標に飛ばす。

			m_myAirVolume = nsPlConstant::INI_AIR_VOLUME;
			m_myAir->SetAirVolume(nsPlConstant::INI_AIR_VOLUME);

			m_respawnFlag = false;

			if (m_gameScene->GetGameState() == nsGSConstant::GAME_STATE_BATTLE)
				m_canMove = true;
		}

		m_respawnCount--;
	}
}