#pragma once
class tklFile
{
public:

	//tkl�t�@�C���Ɋ܂܂��{�[�����
	struct SObject
	{
		std::unique_ptr<char[]> boneName;	//�{�[���̖��O�B
		int parentBoneNo;					//�e�̃{�[���ԍ�
		int boneNo;							//�{�[���ԍ�
		Vector3 bindPose[4];				//�o�C���h�|�[�Y�s��
		Vector3 invBindPose[4];				//�o�C���h�|�[�Y�t�s��
		bool ShadowCasterFlag;				//�V���h�E�L���X�^�[�t���O(���g�p)
		bool ShadowReceiverFlag;			//�V���h�E���V�[�o�[�t���O(���g�p)
		std::vector<int> intData;			//int�̒ǉ��f�[�^
		std::vector<float> floatData;		//float�̒ǉ��f�[�^
		std::vector<char*> stringData;		//������̒ǉ��f�[�^
		std::vector<Vector3> vector3Data;	//Vector3�̒ǉ��f�[�^
	};

	/**
	 * @brief SObject�ɑ΂��ċ��ʂ̏������s��
	 * @param query ���ʏ����̊֐�
	*/
	void QueryObject(std::function<void(SObject& obj)>query)
	{
		for (auto& obj : m_objects)
		{
			query(obj);
		}
	}

	/**
	 * @brief .tkl�t�@�C����ǂݍ���œ��e��SObject�̉ϒ��z��m_objects�ɏ�������
	 * @param levelFilePath tkl�t�@�C���̃p�X
	 * @return ��������?
	*/
	bool Load(const char* levelFilePath);

	/**
	 * @brief �{�[���̐����擾
	 * @return �{�[���̐�
	*/
	int GetNumBone() { return m_numBone; }

	/**
	 * @brief SObject�̉ϒ��z��̃f�[�^���擾
	 * @param index ���Ԗڂ̃f�[�^��
	 * @return SObject�f�[�^
	*/
	SObject& GetObjectAt(int index)
	{
		return m_objects[index];
	}
private:
	int m_tklVersion = 0;						//tkl�t�@�C���̃o�[�W����
	int m_numBone = 0;							//�{�[���̐�
	std::vector<SObject> m_objects;				//SObject�̉ϒ��z��
	typedef std::unique_ptr<SObject> CObject;	//SObject�̃��j�[�N�|�C���^
};

