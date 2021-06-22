#include "stdafx.h"
#include "EffectEngine.h"

EffectEngine* EffectEngine::m_instance = nullptr;	//唯一のインスタンス。

EffectEngine::EffectEngine()
{
	MY_ASSERT(
		m_instance == nullptr,
		"EffectEngineのインスタンスを複数作ることはできません。"
	);
	auto format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	auto d3dDevice = g_graphicsEngine->GetD3DDevice();
	auto commandQueue = g_graphicsEngine->GetCommandQueue();
	// レンダラーを作成。
	m_renderer = ::EffekseerRendererDX12::Create(
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

	//メモリプールの作成。
	m_memoryPool = EffekseerRenderer::CreateSingleFrameMemoryPool(m_renderer->GetGraphicsDevice());

	m_2DmemoryPool = EffekseerRenderer::CreateSingleFrameMemoryPool(m_2Drenderer->GetGraphicsDevice());
	// コマンドリストの作成
	m_commandList = EffekseerRenderer::CreateCommandList(m_renderer->GetGraphicsDevice(), m_memoryPool);

	m_2DcommandList = EffekseerRenderer::CreateCommandList(m_2Drenderer->GetGraphicsDevice(), m_2DmemoryPool);
	// エフェクトマネージャーの作成。
	m_manager = ::Effekseer::Manager::Create(8000);

	m_2Dmanager = ::Effekseer::Manager::Create(8000);

	// 描画モジュールの設定。
	m_manager->SetSpriteRenderer(m_renderer->CreateSpriteRenderer());
	m_manager->SetRibbonRenderer(m_renderer->CreateRibbonRenderer());
	m_manager->SetRingRenderer(m_renderer->CreateRingRenderer());
	m_manager->SetTrackRenderer(m_renderer->CreateTrackRenderer());
	m_manager->SetModelRenderer(m_renderer->CreateModelRenderer());
	
	m_2Dmanager->SetSpriteRenderer(m_2Drenderer->CreateSpriteRenderer());
	m_2Dmanager->SetRibbonRenderer(m_2Drenderer->CreateRibbonRenderer());
	m_2Dmanager->SetRingRenderer(m_2Drenderer->CreateRingRenderer());
	m_2Dmanager->SetTrackRenderer(m_2Drenderer->CreateTrackRenderer());
	m_2Dmanager->SetModelRenderer(m_2Drenderer->CreateModelRenderer());

	// ローダーの設定。
	m_manager->SetTextureLoader(m_renderer->CreateTextureLoader());
	m_manager->SetModelLoader(m_renderer->CreateModelLoader());
	m_manager->SetMaterialLoader(m_renderer->CreateMaterialLoader());
	m_manager->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());

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
		//ロード済み。
		effect = it->second;
	}
	else {
		//新規
		effect = Effekseer::Effect::Create(m_manager, filePath);
		m_effectMap.insert({ u16FilePath, effect });
	}

	return effect;
}
int EffectEngine::Play(Effekseer::EffectRef effect)
{
	//NOTE:handleは作られたエフェクトが何番目かという感じだった。
	//別々にPlayが呼ばれることはないので同じhandleを返してもおそらく大丈夫?
	auto handle = m_manager->Play(effect, 0, 0, 0);
	return handle;
}
void EffectEngine::Stop(int effectHandle)
{
	m_manager->StopEffect(effectHandle);
}


void EffectEngine::Update(float deltaTime)
{
	//NOTE:カメラの番号を受け取り分岐。

	m_memoryPool->NewFrame();

	// Begin a command list
	// コマンドリストを開始する。
	EffekseerRendererDX12::BeginCommandList(m_commandList, g_graphicsEngine->GetCommandList());
	m_renderer->SetCommandList(m_commandList);

	m_manager->Update();

	//レンダラーにカメラ行列を設定。
	m_renderer->SetCameraMatrix(*(const Effekseer::Matrix44*)&g_camera3D->GetViewMatrix());
	
	//レンダラーにプロジェクション行列を設定。
	m_renderer->SetProjectionMatrix(*(const Effekseer::Matrix44*)&g_camera3D->GetProjectionMatrix());

	m_renderer->SetTime(deltaTime);
}

void EffectEngine::Draw(int cameraNum)
{
	//NOTE:カメラの番号を受け取り分岐。

	// Begin to rendering effects
	// エフェクトの描画開始処理を行う。
	m_renderer->BeginRendering();

	// Render effects
	// エフェクトの描画を行う。
	m_manager->Draw();

	// Finish to rendering effects
	// エフェクトの描画終了処理を行う。
	m_renderer->EndRendering();

	// Finish a command list
	// コマンドリストを終了する。
	m_renderer->SetCommandList(nullptr);
	EffekseerRendererDX12::EndCommandList(m_commandList);
}

Effekseer::EffectRef EffectEngine::LoadEffect2D(const char16_t* filePath)
{
	std::u16string u16FilePath = filePath;
	Effekseer::EffectRef effect;
	auto it = m_effectMap.find(u16FilePath);
	if (it != m_effectMap.end()) {
		//ロード済み。
		effect = it->second;
		m_effectMap.insert({ u16FilePath, effect });
	}
	else {
		//新規

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
	//NOTE:カメラの番号を受け取り分岐。

	m_2DmemoryPool->NewFrame();

	// Begin a command list
	// コマンドリストを開始する。
	EffekseerRendererDX12::BeginCommandList(m_2DcommandList, g_graphicsEngine->GetCommandList());
	m_2Drenderer->SetCommandList(m_2DcommandList);

	m_2Dmanager->Update();

	//レンダラーにカメラ行列を設定。
	m_2Drenderer->SetCameraMatrix(*(const Effekseer::Matrix44*)&g_camera2D->GetViewMatrix());
	//レンダラーにプロジェクション行列を設定。
	m_2Drenderer->SetProjectionMatrix(*(const Effekseer::Matrix44*)&g_camera2D->GetProjectionMatrix());

	m_2Drenderer->SetTime(deltaTime);
}

void EffectEngine::Draw2D()
{
	//NOTE:カメラの番号を受け取り分岐。

	// Begin to rendering effects
	// エフェクトの描画開始処理を行う。
	m_2Drenderer->BeginRendering();

	// Render effects
	// エフェクトの描画を行う。
	m_2Dmanager->Draw();

	// Finish to rendering effects
	// エフェクトの描画終了処理を行う。
	m_2Drenderer->EndRendering();

	// Finish a command list
	// コマンドリストを終了する。
	m_2Drenderer->SetCommandList(nullptr);
	EffekseerRendererDX12::EndCommandList(m_2DcommandList);
}