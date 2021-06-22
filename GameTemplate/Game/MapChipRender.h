#pragma once
//���x���̃I�u�W�F�N�g���
struct LevelObjectData
{
	Vector3 position = Vector3::Zero;			//�I�u�W�F�N�g�̍��W
	Quaternion rotation = Quaternion::Identity;	//�I�u�W�F�N�g�̉�]
	Vector3 scale = Vector3::One;				//�I�u�W�F�N�g�̊g�嗦
	const char* name = nullptr;					//�I�u�W�F�N�g�̖��O
};

class MapChipRender : public IGameObject
{
public:
	MapChipRender();
	~MapChipRender();

	/**
	 * @brief ������
	*/
	void Init();

	/**
	 * @brief ���f���̃I�u�W�F�N�g����o�^
	 * @param objData �I�u�W�F�N�g���
	*/
	void AddRenderObject(LevelObjectData objData)
	{
		m_renderObjectData = objData;
	}

private:
	LevelObjectData m_renderObjectData;					//�I�u�W�F�N�g�̃f�[�^
	SkinModelRender* m_modelRender = nullptr;	//�I�u�W�F�N�g��SkinModelRender
	PhysicsStaticObject m_physicsStaticObject;			//�I�u�W�F�N�g��PhysicsStaticObject
};


