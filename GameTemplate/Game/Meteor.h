#pragma once

namespace nsBalloon{
	namespace nsMConstant {
		const int LANDING_SPEED = 50;		
	}
class Meteor :public IGameObject
{
public:
	~Meteor();
	bool Start();
	void Update();

	void SetPosition(Vector3 pos) { m_position = pos; }
	Vector3 GetPosition() { return m_position; }
	void SetTilePosition(Vector3 pos) { m_tilePosition = pos; }
	void Landing();//—Ž‰º‚·‚é
private:
	SkinModelRender* m_skinModelRender = nullptr;
	Vector3 m_position=Vector3::Zero;
	Vector3 m_tilePosition=Vector3::Zero;
	Vector3 m_diffVec = Vector3::Zero;

	SoundSource* m_ssMeteor = nullptr;
	Effect m_fireEff;

};
}