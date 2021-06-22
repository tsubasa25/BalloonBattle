#include "stdafx.h"
#include "EffectEngine.h"

EffectEngine* EffectEngine::m_instance = nullptr;	//�B��̃C���X�^���X�B

EffectEngine::EffectEngine()
{
	MY_ASSERT(
		m_instance == nullptr,
		"EffectEngine�̃C���X�^���X�𕡐���邱�Ƃ͂ł��܂���B"
	);
	auto format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	auto d3dDevice = g_graphicsEngine->GetD3DDevice();
	auto commandQueue = g_graphicsEngine->GetCommandQueue();
	// �����_���[���쐬�B
	m_renderer[0] = ::EffekseerRendererDX12::Create(
		d3dDevice,
		commandQueue,
		3,
		&format,
		1,
		DXGI_FORMAT_D32_FLOAT,
		false,
		8000
	);
	m_2Drenderer = ::EffekseerRendererDX12::Create(
		d3dDevice,
		commandQueue,
		3,
		&format,
		1,
		DXGI_FORMAT_D32_FLOAT,
		false,
		8000
	);

	//�������v�[���̍쐬�B
	m_memoryPool[0] = EffekseerRenderer::CreateSingleFrameMemoryPool(m_renderer[0]->GetGraphicsDevice());

	m_2DmemoryPool = EffekseerRenderer::CreateSingleFrameMemoryPool(m_2Drenderer->GetGraphicsDevice());
	// �R�}���h���X�g�̍쐬
	m_commandList[0] = EffekseerRenderer::CreateCommandList(m_renderer[0]->GetGraphicsDevice(), m_memoryPool[0]);

	m_2DcommandList = EffekseerRenderer::CreateCommandList(m_2Drenderer->GetGraphicsDevice(), m_2DmemoryPool);
	// �G�t�F�N�g�}�l�[�W���[�̍쐬�B
	m_manager[0] = ::Effekseer::Manager::Create(8000);

	m_2Dmanager = ::Effekseer::Manager::Create(8000);

	// �`�惂�W���[���̐ݒ�B
	m_manager[0]->SetSpriteRenderer(m_renderer[0]->CreateSpriteRenderer());
	m_manager[0]->SetRibbonRenderer(m_renderer[0]->CreateRibbonRenderer());
	m_manager[0]->SetRingRenderer(m_renderer[0]->CreateRingRenderer());
	m_manager[0]->SetTrackRenderer(m_renderer[0]->CreateTrackRenderer());
	m_manager[0]->SetModelRenderer(m_renderer[0]->CreateModelRenderer());
	
	m_2Dmanager->SetSpriteRenderer(m_2Drenderer->CreateSpriteRenderer());
	m_2Dmanager->SetRibbonRenderer(m_2Drenderer->CreateRibbonRenderer());
	m_2Dmanager->SetRingRenderer(m_2Drenderer->CreateRingRenderer());
	m_2Dmanager->SetTrackRenderer(m_2Drenderer->CreateTrackRenderer());
	m_2Dmanager->SetModelRenderer(m_2Drenderer->CreateModelRenderer());

	// ���[�_�[�̐ݒ�B
	m_manager[0]->SetTextureLoader(m_renderer[0]->CreateTextureLoader());
	m_manager[0]->SetModelLoader(m_renderer[0]->CreateModelLoader());
	m_manager[0]->SetMaterialLoader(m_renderer[0]->CreateMaterialLoader());
	m_manager[0]->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());

	m_2Dmanager->SetTextureLoader(m_2Drenderer->CreateTextureLoader());
	m_2Dmanager->SetModelLoader(m_2Drenderer->CreateModelLoader());
	m_2Dmanager->SetMaterialLoader(m_2Drenderer->CreateMaterialLoader());
	m_2Dmanager->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());
}
Effekseer::EffectRef EffectEngine::LoadEffect(const char16_t* filePath)
{
	std::u16string u16FilePath = filePath;
	Effekseer::EffectRef effect;
	auto it = m_effectMap.find(u16FilePath);
	if (it != m_effectMap.end()) {
		//���[�h�ς݁B
		effect = it->second;
	}
	else {
		//�V�K
		effect = Effekseer::Effect::Create(m_manager[0], filePath);
		m_effectMap.insert({ u16FilePath, effect });
	}

	return effect;
}
int EffectEngine::Play(Effekseer::EffectRef effect)
{
	//NOTE:handle�͍��ꂽ�G�t�F�N�g�����Ԗڂ��Ƃ��������������B
	//�ʁX��Play���Ă΂�邱�Ƃ͂Ȃ��̂œ���handle��Ԃ��Ă������炭���v?
	auto handle = m_manager[0]->Play(effect, 0, 0, 0);
	return handle;
}
void EffectEngine::Stop(int effectHandle)
{
	m_manager[0]->StopEffect(effectHandle);
}


void EffectEngine::Update(float deltaTime)
{
	//NOTE:�J�����̔ԍ����󂯎�蕪��B

	m_memoryPool[0]->NewFrame();

	// Begin a command list
	// �R�}���h���X�g���J�n����B
	EffekseerRendererDX12::BeginCommandList(m_commandList[0], g_graphicsEngine->GetCommandList());
	m_renderer[0]->SetCommandList(m_commandList[0]);

	m_manager[0]->Update();

	//�����_���[�ɃJ�����s���ݒ�B
	m_renderer[0]->SetCameraMatrix(*(const Effekseer::Matrix44*)&g_camera3D->GetViewMatrix());
	
	//�����_���[�Ƀv���W�F�N�V�����s���ݒ�B
	m_renderer[0]->SetProjectionMatrix(*(const Effekseer::Matrix44*)&g_camera3D->GetProjectionMatrix());

	m_renderer[0]->SetTime(deltaTime);
}

void EffectEngine::Draw(int cameraNum)
{
	//NOTE:�J�����̔ԍ����󂯎�蕪��B

	// Begin to rendering effects
	// �G�t�F�N�g�̕`��J�n�������s���B
	m_renderer[0]->BeginRendering();

	// Render effects
	// �G�t�F�N�g�̕`����s���B
	m_manager[0]->Draw();

	// Finish to rendering effects
	// �G�t�F�N�g�̕`��I���������s���B
	m_renderer[0]->EndRendering();

	// Finish a command list
	// �R�}���h���X�g���I������B
	m_renderer[0]->SetCommandList(nullptr);
	EffekseerRendererDX12::EndCommandList(m_commandList[0]);
}

Effekseer::EffectRef EffectEngine::LoadEffect2D(const char16_t* filePath)
{
	std::u16string u16FilePath = filePath;
	Effekseer::EffectRef effect;
	auto it = m_effectMap.find(u16FilePath);
	if (it != m_effectMap.end()) {
		//���[�h�ς݁B
		effect = it->second;
		m_effectMap.insert({ u16FilePath, effect });
	}
	else {
		//�V�K

		effect = Effekseer::Effect::Create(m_2Dmanager, filePath);
	}

	return effect;
}
int EffectEngine::Play2D(Effekseer::EffectRef effect)
{
	auto handle = m_2Dmanager->Play(effect, 0, 0, 0);
	return handle;
}
void EffectEngine::Stop2D(int effectHandle)
{
	m_2Dmanager->StopEffect(effectHandle);
}


void EffectEngine::Update2D(float deltaTime)
{
	//NOTE:�J�����̔ԍ����󂯎�蕪��B

	m_2DmemoryPool->NewFrame();

	// Begin a command list
	// �R�}���h���X�g���J�n����B
	EffekseerRendererDX12::BeginCommandList(m_2DcommandList, g_graphicsEngine->GetCommandList());
	m_2Drenderer->SetCommandList(m_2DcommandList);

	m_2Dmanager->Update();

	//�����_���[�ɃJ�����s���ݒ�B
	m_2Drenderer->SetCameraMatrix(*(const Effekseer::Matrix44*)&g_camera2D->GetViewMatrix());
	//�����_���[�Ƀv���W�F�N�V�����s���ݒ�B
	m_2Drenderer->SetProjectionMatrix(*(const Effekseer::Matrix44*)&g_camera2D->GetProjectionMatrix());

	m_2Drenderer->SetTime(deltaTime);
}

void EffectEngine::Draw2D()
{
	//NOTE:�J�����̔ԍ����󂯎�蕪��B

	// Begin to rendering effects
	// �G�t�F�N�g�̕`��J�n�������s���B
	m_2Drenderer->BeginRendering();

	// Render effects
	// �G�t�F�N�g�̕`����s���B
	m_2Dmanager->Draw();

	// Finish to rendering effects
	// �G�t�F�N�g�̕`��I���������s���B
	m_2Drenderer->EndRendering();

	// Finish a command list
	// �R�}���h���X�g���I������B
	m_2Drenderer->SetCommandList(nullptr);
	EffekseerRendererDX12::EndCommandList(m_2DcommandList);
}