#pragma once
namespace nsBalloon{
	namespace nsTConstant {
		const int DELAY_COUNT = 20;
	}
	class Thunder :public IGameObject
	{
	public: 
		~Thunder();
		bool Start();
		void Update();
	
		void SetPosition(const Vector3& pos) { m_position = pos; }
	private:
		Vector3 m_position = Vector3::Zero;
		Effect m_thunderEff;
		int m_loopCount;
	};
}