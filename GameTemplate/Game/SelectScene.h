#pragma once
namespace nsBalloon {
	namespace nsSSConstant
	{
		const Vector3 BUIL_BALL_POS = { 200.f,50.f,0.f };//ビル用風船の位置
		const Vector3 SKY_BALL_POS = { 500,50,0 };//空島用風船の位置
		const Vector3 TRAP_BALL_POS = { 200,-200,0 };//トラップ用風船の位置	
		const Vector3 RANDAM_BALL_POS{ 500,-200,0 };//ランダム風船用の位置
		const Vector3 P1_POS = { -550,100,0 };//P1用風船の位置
		const Vector3 P2_POS = { -410,100,0 };//P2用風船の位置
		const Vector3 P3_POS = { -270,100,0 };//P3用風船の位置
		const Vector3 P4_POS = { -130,100,0 };//P4用風船の位置
		const Vector3 P5_POS = { -550,-80,0 };//P5用風船の位置
		const Vector3 P6_POS = { -410,-80,0 };//P6用風船の位置
		const Vector3 P7_POS = { -270,-80,0 };//P7用風船の位置
		const Vector3 P8_POS = { -130,-80,0 };//P8用風船の位置

		const float SOUND_SELECT_BGM_VOLUME = 0.2f;//セレクト画面用BGMの音量
		const float SOUND_SELECT_SE_VOLUME = 0.6f;//選択時の音量
	}
	class SelectScene :public IGameObject
	{
	public:
		bool Start();
		void Update();
		~SelectScene();
		/// <summary>
		/// プレイヤー人数を選択
		/// </summary>
		void SelectionPlayerCount();
		/// <summary>
		/// ストック数を選択
		/// </summary>
		void SelectionStockNumber();
		/// <summary>
		/// ステージを選択
		/// </summary>
		void SelectionStage();
	private:
		/// <summary>
		/// プレイヤー人数画像
		/// </summary>
		SpriteRender* m_cPlayerCount_Sprite;
		/// <summary>
		/// ストック数画像
		/// </summary>
		SpriteRender* m_cStockNum_Sprite;
		/// <summary>
		/// プレイヤーのOK画像
		/// </summary>
		SpriteRender* m_okPlayer_Sprite;
		/// <summary>
		/// ストックのOK画像
		/// </summary>
		SpriteRender* m_okStok_Sprite;
		/// <summary>
		/// プレイヤーの<<>>画像
		/// </summary>
		SpriteRender* m_arrowPlayer_Sprite;
		/// <summary>
		/// ストック数の<<>>画像
		/// </summary>
		SpriteRender* m_arrowStock_Sprite;
		/// <summary>
		/// 雲文字「プレイヤー」
		/// </summary>
		SpriteRender* m_cPlayer_Sprite;//
		/// <summary>
		/// 雲文字「ストック」
		/// </summary>
		SpriteRender* m_cStock_Sprite;
		/// <summary>
		/// 雲文字「ステージ」
		/// </summary>
		SpriteRender* m_cStage_Sprite;
		/// <summary>
		/// ステージ画像
		/// </summary>
		SpriteRender* m_stageBalloon_Sprite[4] = { nullptr,nullptr,nullptr,nullptr };//空島、ビル、トラップ、おまかせ	
		/// <summary>
		/// プレイヤーの風船画像
		/// </summary>
		SpriteRender* m_playerUI_Sprite[PLAYER_MAX_COUNT] = { nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr };
		/// <summary>
		/// 雲文字「ストック」の位置
		/// </summary>
		Vector3 m_cPlayerPos = { -350,250,0 };
		/// <summary>
		/// 雲文字「ストック」の位置
		/// </summary>
		Vector3 m_cStockPos = { -350,-250,0 };
		/// <summary>
		/// 雲文字「ステージ」の位置
		/// </summary>
		Vector3 m_StagePos = { 350,250,0 };
		/// <summary>
		/// プレイヤー人数画像の位置
		/// </summary>
		Vector3 m_cPlayerNumPos = { 0,250,0 };
		/// <summary>
		/// ストック数画像の位置
		/// </summary>
		Vector3 m_cStockNumPos = { 0,-250,0 };
		/// <summary>
		/// プレイヤー人数用《》画像の位置
		/// </summary>
		Vector3 m_arrowPlayerPos = { 0,250,0 };
		/// <summary>
		/// ストック数用《》画像の位置
		/// </summary>
		Vector3 m_arrowStockPos = { 0,-250,0 };
		/// <summary>
		/// プレイヤー人数用OK!画像の位置
		/// </summary>
		Vector3 m_okPlayerPos = { 0,250,0 };
		/// <summary>
		/// ストック数用OK!画像の位置
		/// </summary>
		Vector3 m_okStockPos = { 0,-250,0 };
		/// <summary>
		/// ステージ表示用風船画像の位置
		/// </summary>
		Vector3 m_stageBalloonPos[4] = { {nsSSConstant::SKY_BALL_POS},{nsSSConstant::BUIL_BALL_POS},{nsSSConstant::TRAP_BALL_POS},{nsSSConstant::RANDAM_BALL_POS} };
		/// <summary>
		/// プレイヤー風船画像の位置
		/// </summary>
		Vector3 m_playerUIPos[PLAYER_MAX_COUNT] = { { nsSSConstant::P1_POS },{ nsSSConstant::P2_POS },{ nsSSConstant::P3_POS },{ nsSSConstant::P4_POS },{ nsSSConstant::P5_POS },{nsSSConstant::P6_POS },{ nsSSConstant::P7_POS },{ nsSSConstant::P8_POS } };
		/// <summary>
		/// セレクト画面用のBGM
		/// </summary>
		SoundSource* m_selectBGM = nullptr;
		/// <summary>
		/// 選択時のSE
		/// </summary>
		SoundSource* m_selectSE = nullptr;
		/// <summary>
		/// キャンセル時のSE
		/// </summary>
		SoundSource* m_cancelSE = nullptr;
		/// <summary>
		/// タイトルに戻りますか？用の画像
		/// </summary>
		FontRender* m_titleBackFont = nullptr;
		/// <summary>
		/// タイトルの状態
		/// </summary>
		enum TitleState
		{
			enBackTitle,	//タイトルへ戻るか選択する。
			enPlayerNum,//プレイヤー人数選択状態
			enPlayerStock,//プレイヤーストック選択状態
			enStageSelect//ステージ選択状態
		};
		/// <summary>
		/// 現在のタイトルの状態
		/// </summary>
		TitleState m_titleState = enPlayerNum;
		/// <summary>
		/// プレイヤー人数
		/// </summary>
		int m_playerCount = 2;
		/// <summary>
		/// プレイヤーのストック
		/// </summary>
		int m_playerStock = 3;
		/// <summary>
		/// ステージの選択番号
		/// </summary>
		bool m_selectNum[2][2] = { {0,0},{0,0} };
		/// <summary>
		/// ステージ選択番号のX軸
		/// </summary>
		int m_XNum = 0;
		/// <summary>
		/// ステージ選択番号のY軸
		/// </summary>
		int m_YNum = 0;
		/// <summary>
		/// セレクト画面のループカウント
		/// </summary>
		float m_selectLoopCount = 0;
		/// <summary>
		/// ステージ番号0:空島,1:ビル,2:トラップ,3:おまかせ
		/// </summary>
		int m_stageNum = 0;
		/// <summary>
		/// 矢印点滅用ループカウント
		/// </summary>
		int m_arrowLoopCount = 0;
		/// <summary>
		/// 矢印を点滅させるか
		/// </summary>
		bool m_arrowFlag = false;
		/// <summary>
		/// 矢印が点滅する時間
		/// </summary>
		int m_arrowSwichTime = 20;



	};
}