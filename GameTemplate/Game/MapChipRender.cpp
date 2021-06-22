#include "stdafx.h"
#include "MapChipRender.h"
#include "Level.h"

	MapChipRender::MapChipRender()
	{

	}

	MapChipRender::~MapChipRender()
	{
		//�쐬���������������B
		DeleteGO(m_modelRender);
	}

	void MapChipRender::Init()
	{

		//�X�L�����f�������_���[���쐬
		m_modelRender = NewGO<SkinModelRender>(0);
		//�t�@�C���p�X���쐬�B
		char filepath[256];
		sprintf_s(filepath, "Assets/modelData/%s.tkm", m_renderObjectData.name);
		m_modelRender->Init(filepath);

		m_modelRender->SetPosition(m_renderObjectData.position);
		m_modelRender->SetRotation(m_renderObjectData.rotation);
		m_modelRender->SetScale(m_renderObjectData.scale);

		//�����蔻����쐬�B
		m_physicsStaticObject.CreateFromModel(m_modelRender->GetModel(), m_modelRender->GetModel().GetWorldMatrix());

		//�e(�\��)

	}
