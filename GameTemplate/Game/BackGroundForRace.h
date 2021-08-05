#pragma once
namespace nsBalloon {
	class BackGroundForRace :public IGameObject
	{
	public:
		~BackGroundForRace();
		bool Start();
		void Update();
	private:
		SkinModelRender* m_skinModelRender = nullptr;
	};
}