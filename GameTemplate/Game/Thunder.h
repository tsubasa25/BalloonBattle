#pragma once

namespace nsBalloon {
	class Thunder :public IGameObject
	{
	public: 
		~Thunder();
		bool Start();
		void Update();
	private:
		Vector3 m_position = Vector3::Zero;

	};
}