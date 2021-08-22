#pragma once
namespace nsBalloon {
	namespace nsBGConstant
	{
		const float RESPAWN_POSITION_HEIGHT = 800.0f;	//���X�|�[������Ƃ��Ƀv���C���[���~��Ă��鍂���B
		const std::wstring STAGE_ZERO_NAME = { L"SkyIsLand Stage" };
		const std::wstring STAGE_ONE_NAME = { L"Building Stage" };
		const std::wstring STAGE_TWO_NAME = { L"Trap Stage" };
		const std::wstring STAGE_THREE_NAME = { L"Tile Stage" };

		const float SOUND_MAP_BGM_VOLUME = 0.2f;
	}
	class Sky;
	class GameScene;
	class Player;
	class GimmickNeedle;
	class MoveRiver;
	class WindTurbine;
	
	class BackGround :public IGameObject
	{

	public:
		~BackGround();
		bool Start();
		void Update();

		Vector3 GetRespawnPosition(int ResPlNum);	//���X�|�[���������v���C���[�̔ԍ���n�����ƂŁA���X�|�[���ʒu���v�Z����B
		void SetStageNum(int num) { m_stageNum = num; };
		int GetStageNum() { return m_stageNum; };
		Vector3 GetWTBladesPos() { return m_WTBladesPos; };
		//Vector3 GetIniSpawnPosition();
		void SetIniPosition();
		std::wstring GetStageName() { return m_stageName; };

	private:
		Sky* m_sky = nullptr;

		MoveRiver* m_moveRiver = nullptr;

		SkinModelRender* m_skinModelRender = nullptr;

		PhysicsStaticObject m_physicsStaticObject;				//CharaCon�Ƃ̓����蔻��Ɏg�p����ÓI�����I�u�W�F�N�g

		WindTurbine* m_windTurbine = nullptr;

		GameScene* m_gameScene = nullptr;
		Level m_level;

		Vector3 m_spawnPos[PLAYER_MAX_COUNT]{ Vector3::Zero,Vector3::Zero,Vector3::Zero,Vector3::Zero,Vector3::Zero,Vector3::Zero,Vector3::Zero,Vector3::Zero, };
		bool m_canRespawn[PLAYER_MAX_COUNT]{ true,true,true,true,true,true,true,true };
		int m_canRespawnInterval[PLAYER_MAX_COUNT]{ 0,0,0,0,0,0,0,0 };


		Vector3 m_WTBladesPos = { Vector3::Zero };

		Vector3 m_enemyMiddlePos = { Vector3::Zero };	//���v���C���[�̃|�W�V�����̕��ϒn�_

		int m_respawnPlayerNum = 0;	//���X�|�[������v���C���[�̔ԍ�

		GimmickNeedle* m_needle = nullptr;

		std::wstring m_stageName = { L"Hoge" };

		SoundSource* m_map1BGM = nullptr;
		SoundSource* m_map2BGM = nullptr;
		SoundSource* m_map3BGM = nullptr;

		int m_stageNum = 0;
	};
}