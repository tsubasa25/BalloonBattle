#pragma once
#include "tklFile.h"
#include "MapChipRender.h"


	class Level
	{
	private:
		/**
		 * @brief �{�[�����쐬����m_bone�Ɋi�[����
		*/
		void BuildBone();
	public:
		~Level();

		/**
		 * @brief ���x���̏�����
		 * @param levelFilePath ���x���̃t�@�C���p�X(.tkl)
		 * @param hookFunc �t�b�N�֐�
		 * @return
		*/
		bool Init(const char* levelFilePath, std::function<bool(LevelObjectData& objectData)> hookFunc);
	private:
		tklFile m_tklFile;								//�ǂݍ���tkl�t�@�C���̃f�[�^
		typedef std::unique_ptr<Bone> CBone;			//�{�[���̃��j�[�N�|�C���^
		std::vector<CBone> m_bone;						//�{�[���̃��j�[�N�|�C���^�̉ϒ��z��
		std::unique_ptr<Matrix[]> m_boneMatrixs;		//�s��̃��j�[�N�|�C���^
		bool m_isInited = false;						//������������������?
		std::list<MapChipRender*> m_mapChipRenderPtrs;	//���x���ɑ��݂���}�b�v�`�b�v�̃��X�g
	};

