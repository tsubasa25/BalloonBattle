#include "stdafx.h"
#include "tklFile.h"

bool tklFile::Load(const char* levelFilePath)
{
	//.tkl�t�@�C�����I�[�v��
	FILE* fp = fopen(levelFilePath, "rb");

	//�J���̂Ɏ��s������false��Ԃ�
	if (fp == nullptr)
	{
		return false;
	}

	//tkl�t�@�C���̃o�[�W�������擾
	fread(&m_tklVersion, sizeof(m_tklVersion), 1, fp);
	//���̐����擾
	fread(&m_numBone, sizeof(m_numBone), 1, fp);

	//���̐������I�u�W�F�N�g��Vector���g������
	m_objects.resize(m_numBone);

	for (int i = 0; i < m_numBone; i++)
	{
		//���̖��O�̕��������擾
		char numBoneName = 0;
		fread(&numBoneName, sizeof(numBoneName), 1, fp);
		auto& object = m_objects.at(i);
		//���̖��O���擾
		object.boneName = std::make_unique<char[]>(numBoneName + 1);
		fread(object.boneName.get(), numBoneName + 1, 1, fp);

		//�e�̍��̔ԍ����擾
		fread(&object.parentBoneNo, sizeof(object.parentBoneNo), 1, fp);

		//���̔ԍ����擾
		object.boneNo = i;

		//�o�C���h�|�[�Y�̍s����擾
		fread(&object.bindPose, sizeof(object.bindPose), 1, fp);

		//�o�C���h�|�[�Y�̋t�s����擾
		fread(&object.invBindPose, sizeof(object.invBindPose), 1, fp);

		//�V���h�E�L���X�^�[�t���O���擾
		fread(&object.ShadowCasterFlag, 1, 1, fp);

		//�V���h�E���V�[�o�[�t���O���擾
		fread(&object.ShadowReceiverFlag, 1, 1, fp);

		//int�p�����[�^�[�̐����擾
		int numIntData = 0;
		fread(&numIntData, sizeof(numIntData), 1, fp);

		//int�p�����[�^�[�̐�����int�p�����[�^�[���擾
		for (int j = 0; j < numIntData; j++)
		{
			int Data = 0;
			fread(&Data, sizeof(Data), 1, fp);

			object.intData.push_back(Data);
		}

		//float�p�����[�^�[�̐����擾
		int numFloatData = 0;
		fread(&numFloatData, sizeof(numFloatData), 1, fp);

		//float�p�����[�^�[�̐�����float�p�����[�^�[���擾
		for (int j = 0; j < numFloatData; j++)
		{
			float Data = 0.0f;
			fread(&Data, sizeof(Data), 1, fp);

			object.floatData.push_back(Data);
		}

		//string�p�����[�^�[�̐����擾
		int numStringData = 0;
		fread(&numStringData, sizeof(numStringData), 1, fp);

		//string�p�����[�^�[�̐�����string�p�����[�^�[���擾
		std::vector<int> stringDataSize;
		for (int j = 0; j < numStringData; j++)
		{
			int DataSize = 0;
			fread(&DataSize, sizeof(DataSize), 1, fp);

			stringDataSize.push_back(DataSize);

			char* Data = nullptr;
			fread(&Data, sizeof(Data), 1, fp);

			object.stringData.push_back(Data);

		}

		//Vector3�f�[�^�̐����擾
		int numVector3Data = 0;
		fread(&numVector3Data, sizeof(numVector3Data), 1, fp);

		//Vector3�f�[�^�̐�����Vector3�f�[�^���擾
		for (int j = 0; j < numVector3Data; j++)
		{
			Vector3 Data = { 0.0f,0.0f,0.0f };
			fread(&Data, sizeof(Data), 1, fp);

			object.vector3Data.push_back(Data);
		}

	}

	return true;
}
