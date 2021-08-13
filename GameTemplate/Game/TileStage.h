#pragma once
namespace nsBalloon {
	class TileStage :public IGameObject
	{
	public:
		bool Start()override;
		void Update()override;
		~TileStage();
	private:
		Level m_level;
		
	};
}