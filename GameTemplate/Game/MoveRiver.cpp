#include "stdafx.h"
#include "MoveRiver.h"
namespace nsBalloon {
	namespace
	{
		const float RIVER_TEXTURE_SIZE = 512.0f;
		const float RIVER_SCROLL_VALUE = 0.1f;
	}
	bool MoveRiver::Start()
	{
		ModelInitData riverInitData;//���f���̏��������
		riverInitData.m_tkmFilePath = "Assets/modelData/River.tkm";//�t�@�C���w��

		//�����Ńe�N�X�`���̃T�C�Y���w��
		m_riverData.textureSize = RIVER_TEXTURE_SIZE;
		//��̏������f�[�^���쐬
		riverInitData.m_fxFilePath = "Assets/shader/SkyBoard.fx";
		riverInitData.m_vsEntryPointFunc = "VSMain";
		riverInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
		riverInitData.m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;
		riverInitData.m_modelUpAxis = enModelUpAxisZ;
		riverInitData.m_expandConstantBuffer[0] = &m_riverData;
		riverInitData.m_expandConstantBufferSize[0] = sizeof(m_riverData);

		m_riverModel.Init(riverInitData);
		m_riverModel.UpdateWorldMatrix(Vector3::Zero, Quaternion::Identity, Vector3::One);

		return true;
	}
	void MoveRiver::Update()
	{
		//�e�N�X�`�����X�N���[��������
		m_riverData.scrollingValue += RIVER_SCROLL_VALUE;

		//�X�N���[���ʂ���̃e�N�X�`���̃T�C�Y�𒴂������������̂�0�ɂ���悤�ɂ��Ă���B
		if (m_riverData.scrollingValue >= m_riverData.textureSize)
		{
			m_riverData.scrollingValue = 0;
		}

	}
	void MoveRiver::Render(RenderContext& rc, Camera* camera)
	{
		if (rc.GetRenderStep() == RenderContext::eStep_Render)
		{
			m_riverModel.Draw(rc, camera);
		}
	}
}