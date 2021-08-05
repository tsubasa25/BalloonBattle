#pragma once
namespace nsBalloon {

	class BackGroundForRace;
	class Player;

	class RaceMode :public IGameObject
	{
	public:
		~RaceMode();
		bool Start();
		void Update();
	private:
		BackGroundForRace* m_backGroundForRace = nullptr;
		//Player* m_player = nullptr;
	};
}