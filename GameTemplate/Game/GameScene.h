#pragma once
#include "Player.h"
namespace nsBalloon {
	namespace nsGSConstant
	{
		const int GAME_STATE_LOOK_STAGE = 1;
		const int GAME_STATE_START_CALL = 2;
		const int GAME_STATE_BATTLE = 3;
		const int GAME_STATE_RESULT = 4;
		const Vector3 INI_CAMERA_POS = { 0.0f, 1200.0f, -1900.0f };
		const Vector3 INI_CAMERA_TARGET_POS = { 0,100,-300 };
		const int INI_GAME_START_CALL_TIME = 150;
		const int INI_LOOK_STAGE_TIME = 300;
		const Vector3 BUTTON_POS_LA = { -250,-300,0 };
		const Vector3 BUTTON_POS_LB = { -50,-300,0 };
		const Vector3 BUTTON_POS_Y = { 125,-300,0 };
		const Vector3 BUTTON_POS_B = { 250,-300,0 };
		const int PLAYER_COUNT = 8;
		const int IMAGE_COUNT = 4;
	}
	class GameScene :public IGameObject
	{
	public:
		~GameScene();
		bool Start();
		void Update();
	private:
		int m_iniPlCount = 0;
		int m_playerCount = 0;
		int m_alivePlCount = 0;

		int m_stock = 0;

		Player* m_player[nsGSConstant::PLAYER_COUNT] = { nullptr,nullptr, nullptr, nullptr,nullptr,nullptr, nullptr, nullptr };
		Vector3 m_iniPos[nsGSConstant::PLAYER_COUNT] = { {Vector3::Zero }, { Vector3::Zero }, { Vector3::Zero}, { Vector3::Zero }, { Vector3::Zero }, {Vector3::Zero }, { Vector3::Zero }, { Vector3::Zero } };//初期位置

		bool m_IsAlive[nsGSConstant::PLAYER_COUNT] = { false,false,false,false,false,false,false,false };//生存確認
		//ライト実験用
		bool aa = true;
		int aaNum = 0;

		//エフェクト実験用
		Effect eff;

		FontRender* m_gameStartFontRender = nullptr;
		int m_gameSceneState = 0;
		int m_gameStartCallTimer = nsGSConstant::INI_GAME_START_CALL_TIME;
		int m_lookStageTimer = nsGSConstant::INI_LOOK_STAGE_TIME;
		FontRender* m_stageNameFontRender = nullptr;
		Vector2 m_stageNamePos = { Vector2::Zero };

		DirectionLight* m_directionLight = nullptr;


		std::wstring m_stageName = { L"Hoge" };

		SpriteRender* m_button_Sprite[nsGSConstant::IMAGE_COUNT] = { nullptr,nullptr, nullptr, nullptr };
		Vector3 m_buttonPos[nsGSConstant::IMAGE_COUNT] = { nsGSConstant::BUTTON_POS_LA ,nsGSConstant::BUTTON_POS_LB ,nsGSConstant::BUTTON_POS_B ,nsGSConstant::BUTTON_POS_Y };

		bool m_isResult = false;

	public:
		Vector3 GetIniPos(int i) { return m_iniPos[i]; }
		void SetPlayerCount(int num) { m_playerCount = num; }
		int GetPlayerCount() { return m_playerCount; }
		//void SetIsAlive(int pNum, bool alive) { m_IsAlive[pNum] = alive; }

		void LookStage();
		void GameStartCall();
		void Battle();

		void SetStock(int num) { m_stock = num; }
		int GetStock() { return m_stock; }

		void SetIniPosition();
		void SetGameState(int num) { m_gameSceneState = num; };
		int GetGameState() { return m_gameSceneState; };

		int GetIniPlayerCount() { return m_iniPlCount; }


	};
}