#include "stdafx.h"
#include "Level.h"
namespace nsBalloon {
	Level::~Level()
	{
		for (auto mapChipRender : m_mapChipRenderPtrs)
		{
			DeleteGO(mapChipRender);
		}
	}

	bool Level::Init(const char* levelFilePath, std::function<bool(LevelObjectData& objectData)> hookFunc)
	{
		m_tklFile.Load(levelFilePath);

		BuildBone();

		for (auto i = 1; i < m_bone.size(); i++)
		{
			//�����擾
			auto bone = m_bone[i].get();

			if (bone->GetParentBoneNo() == 0)
			{
				LevelObjectData objData;

				//objData�̊e�����o�Ƀ{�[������l������
				//���W�A��]�A�g�嗦
				bone->CalcWorldTRS(objData.position, objData.rotation, objData.scale);

				//���O�B
				objData.name = m_tklFile.GetObjectAt(i).boneName.get();

				//3dsMax�Ƃ͎����Ⴄ�̂ŁA�␳������B
				float t = objData.position.y;
				objData.position.y = objData.position.z;
				objData.position.z = -t;

				t = objData.rotation.y;
				objData.rotation.y = objData.rotation.z;
				objData.rotation.z = -t;

				std::swap(objData.scale.y, objData.scale.z);

				auto isHook = false;

				if (hookFunc != nullptr)
				{
					//hook�֐����w�肳��Ă���̂�Hook�֐����Ăяo���B
					isHook = hookFunc(objData);
				}

				if (isHook == false)
				{
					//�}�b�v�`�b�v�����_�[���쐬����B
					MapChipRender* pMapChipRender = NewGO<MapChipRender>(0);
					//�{�[������擾�����I�u�W�F�N�g�̃f�[�^���擾
					pMapChipRender->AddRenderObject(objData);
					//���x���̃}�b�v�`�b�v�����_�[�̉ϒ��z��ɒǉ�
					m_mapChipRenderPtrs.push_back(pMapChipRender);
				}
			}
		}

		//���ׂẴ}�b�v�`�b�v�����_�[������������
		for (auto& mapChipRender : m_mapChipRenderPtrs)
		{
			mapChipRender->Init();
		}
		return true;
	}

	void Level::BuildBone()
	{
		m_tklFile.QueryObject([&](tklFile::SObject& tklObj)
			{
				//�o�C���h�|�[�Y�̍s��
				//�����̃X�P���g���̃|�[�Y�AT�|�[�Y��A�|�[�Y�݂����Ȃ��̂炵���B
				Matrix bindPoseMatrix;
				memcpy(bindPoseMatrix.m[0], &tklObj.bindPose[0], sizeof(tklObj.bindPose[0]));
				memcpy(bindPoseMatrix.m[1], &tklObj.bindPose[1], sizeof(tklObj.bindPose[1]));
				memcpy(bindPoseMatrix.m[2], &tklObj.bindPose[2], sizeof(tklObj.bindPose[2]));
				memcpy(bindPoseMatrix.m[3], &tklObj.bindPose[3], sizeof(tklObj.bindPose[3]));

				bindPoseMatrix.m[0][3] = 0.0f;
				bindPoseMatrix.m[1][3] = 0.0f;
				bindPoseMatrix.m[2][3] = 0.0f;
				bindPoseMatrix.m[3][3] = 1.0f;

				//�o�C���h�|�[�Y�̋t�s��B
				Matrix invBindPoseMatrix;
				memcpy(invBindPoseMatrix.m[0], &tklObj.invBindPose[0], sizeof(tklObj.invBindPose[0]));
				memcpy(invBindPoseMatrix.m[1], &tklObj.invBindPose[1], sizeof(tklObj.invBindPose[1]));
				memcpy(invBindPoseMatrix.m[2], &tklObj.invBindPose[2], sizeof(tklObj.invBindPose[2]));
				memcpy(invBindPoseMatrix.m[3], &tklObj.invBindPose[3], sizeof(tklObj.invBindPose[3]));
				invBindPoseMatrix.m[0][3] = 0.0f;
				invBindPoseMatrix.m[1][3] = 0.0f;
				invBindPoseMatrix.m[2][3] = 0.0f;
				invBindPoseMatrix.m[3][3] = 1.0f;

				//�{�[�����B
				wchar_t boneName[256];

				//tkl�̃I�u�W�F�N�g���̌^�����C�h�����ɕϊ��B
				mbstowcs(boneName, tklObj.boneName.get(), 256);

				//�{�[�����쐬
				CBone bone = std::make_unique<Bone>(
					boneName,
					bindPoseMatrix,
					invBindPoseMatrix,
					tklObj.parentBoneNo,
					tklObj.boneNo
					);

				//�쐬�����{�[����ǉ��B(���[�u)
				m_bone.push_back(std::move(bone));


				//�{�[���̌v�Z?
				for (auto& bone : m_bone)
				{
					if (bone->GetParentBoneNo() != -1)
					{
						m_bone.at(bone->GetParentBoneNo())->AddChild(bone.get());
						//���[�J���}�g���N�X�v�Z
						const Matrix& parentMatrix = m_bone.at(bone->GetParentBoneNo())->GetInvBindPoseMatrix();
						Matrix localMatrix;
						//���s�ړ��s��͂��������B
						localMatrix = bone->GetBindPoseMatrix() * parentMatrix;
						bone->SetLocalMatrix(localMatrix);
					}
					else
					{
						//����ȏ�e�����Ȃ��B
						bone->SetLocalMatrix(bone->GetBindPoseMatrix());
					}
				}

				//�{�[���s����m��
				m_boneMatrixs = std::make_unique<Matrix[]>(m_bone.size());

				//�������I���B
				m_isInited = true;
			}
		);
	}
}