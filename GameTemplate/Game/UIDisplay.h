#pragma once
namespace nsBalloon {
	namespace nsUIDConstant
	{
		const Vector3 PLAYER1UI_POS = { -550, 290,0 };
		const Vector3 PLAYER2UI_POS = { 550,290,0 };
		const Vector3 PLAYER3UI_POS = { -550,115,0 };
		const Vector3 PLAYER4UI_POS = { 550,115,0 };
		const Vector3 PLAYER5UI_POS = { -550,-65,0 };
		const Vector3 PLAYER6UI_POS = { 550,-65,0 };
		const Vector3 PLAYER7UI_POS = { -550,-245,0 };
		const Vector3 PLAYER8UI_POS = { 550,-245,0 };

		const Vector3 PLAYER1STOCK_POS = { -575,208,0 };
		const Vector3 PLAYER2STOCK_POS = { 525, 208, 0 };
		const Vector3 PLAYER3STOCK_POS = { -575,33,0 };
		const Vector3 PLAYER4STOCK_POS = { 525,33,0 };
		const Vector3 PLAYER5STOCK_POS = { -575,-147,0 };
		const Vector3 PLAYER6STOCK_POS = { 525,-147,0 };
		const Vector3 PLAYER7STOCK_POS = { -575,-327,0 };
		const Vector3 PLAYER8STOCK_POS = { 525,-327,0 };

		const int STOCK_MAX_COUNT = 10;

		const Vector3 PLAYER_UI_SIZE = { 0.3f,0.3f,0.3f };
		const Vector3 PLAYER_STOCK_SIZE = { 0.3f,0.3f,0.3f };
		const float STOCKNUM_SIZE = { 0.9f };
		const Vector4 STOCKNUM_COLOR = { 1.0f,1.0f,1.0f,1.0f };
		const Vector2 PL_STOCKNUM_POS[8] = { { -550,230 }, {550,230 }, { -550,55 }, { 550,55 }, { -550,-125 }, { 550,-125 }, { -550,-305 },	{550, -305 } };
		const int STOCK_UI_SIZE = 128;
	}
	class UIDisplay : public IGameObject
	{
	public:
		bool Start();
		void Update();
		~UIDisplay();
		void SetPlayerDeath(int PldeathNum) { m_PlDeath[PldeathNum] = true; };
		void SetPlayerDecStock(int PldecstockNum) { m_PlDecStock[PldecstockNum] = true; };

		void SetPlayerStock(int stock, int plNum);

		void SetIsDeath(bool flag) { m_isDeath = flag; }

		void SetIsMinus(int pnum) { m_isMinus[pnum] = true; }
		void SetIsPlus(int pnum) { m_isPlus[pnum] = true; }

		void MinusDisplay(int pnum);

	private:

		std::wstring m_stocknum[nsUIDConstant::STOCK_MAX_COUNT] = { {L"x0"},{L"x1"},{L"x2"},{L"x3"},{L"x4"},{L"x5"}, {L"x6"},{L"x7"},{L"x8"},{L"x9"} };

		SpriteRender* m_playerUI_Sprite[PLAYER_MAX_COUNT] = { nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr };

		SpriteRender* m_playerstock_Sprite[PLAYER_MAX_COUNT] = { nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr };

		SpriteRender* m_minusPoint_Sprite[PLAYER_MAX_COUNT] = { nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr };
		SpriteRender* m_plusPoint_Sprite[PLAYER_MAX_COUNT] = { nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr };

		Vector3 m_playerUI_Pos[PLAYER_MAX_COUNT] = {
		{ nsUIDConstant::PLAYER1UI_POS },
		{ nsUIDConstant::PLAYER2UI_POS },
		{ nsUIDConstant::PLAYER3UI_POS },
		{ nsUIDConstant::PLAYER4UI_POS },
		{ nsUIDConstant::PLAYER5UI_POS },
		{ nsUIDConstant::PLAYER6UI_POS },
		{ nsUIDConstant::PLAYER7UI_POS },
		{ nsUIDConstant::PLAYER8UI_POS } };

		Vector3 m_playerstock_Pos[PLAYER_MAX_COUNT] = {
		{ nsUIDConstant::PLAYER1STOCK_POS },
		{ nsUIDConstant::PLAYER2STOCK_POS },
		{ nsUIDConstant::PLAYER3STOCK_POS },
		{ nsUIDConstant::PLAYER4STOCK_POS },
		{ nsUIDConstant::PLAYER5STOCK_POS },
		{ nsUIDConstant::PLAYER6STOCK_POS },
		{ nsUIDConstant::PLAYER7STOCK_POS },
		{ nsUIDConstant::PLAYER8STOCK_POS } };

		Vector3 m_minusPointPos[PLAYER_MAX_COUNT] = {
		{ nsUIDConstant::PLAYER1UI_POS },
		{ nsUIDConstant::PLAYER2UI_POS },
		{ nsUIDConstant::PLAYER3UI_POS },
		{ nsUIDConstant::PLAYER4UI_POS },
		{ nsUIDConstant::PLAYER5UI_POS },
		{ nsUIDConstant::PLAYER6UI_POS },
		{ nsUIDConstant::PLAYER7UI_POS },
		{ nsUIDConstant::PLAYER8UI_POS } };

		Vector3 m_plusPointPos[PLAYER_MAX_COUNT] = {
		{ nsUIDConstant::PLAYER1UI_POS },
		{ nsUIDConstant::PLAYER2UI_POS },
		{ nsUIDConstant::PLAYER3UI_POS },
		{ nsUIDConstant::PLAYER4UI_POS },
		{ nsUIDConstant::PLAYER5UI_POS },
		{ nsUIDConstant::PLAYER6UI_POS },
		{ nsUIDConstant::PLAYER7UI_POS },
		{ nsUIDConstant::PLAYER8UI_POS } };

		FontRender* m_playerstock_FontRender[PLAYER_MAX_COUNT] = { nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr };

		int loopcount = 0;
		int explosioncount[PLAYER_MAX_COUNT] = { 0,0,0,0,0,0,0,0 };
		int changeframenum[4] = { 1, 10 , 20, 40 };
		bool m_PlDecStock[PLAYER_MAX_COUNT] = { false,false,false,false,false,false,false,false };
		bool m_PlDeath[PLAYER_MAX_COUNT] = { false,false,false,false,false,false,false,false };
		bool m_isDeath = false;
		bool m_isMinus[PLAYER_MAX_COUNT] = { false,false,false,false,false,false,false,false };
		bool m_isPlus[PLAYER_MAX_COUNT] = { false,false,false,false,false,false,false,false };
		int m_pointMinusLoop[PLAYER_MAX_COUNT] = { 0,0,0,0,0,0,0,0 };
		int m_pointPlusLoop[PLAYER_MAX_COUNT] = { 0,0,0,0,0,0,0,0 };
	};
}