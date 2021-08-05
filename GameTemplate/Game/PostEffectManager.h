#pragma once
#include "GaussianBlur.h"
namespace nsBalloon {
	class PostEffectManager
	{
	private:
		PostEffectManager() = default;
		~PostEffectManager() = default;

		static PostEffectManager* m_instance;
	public:
		static void CreateInstance()
		{
			if (!m_instance)
			{
				m_instance = new PostEffectManager;
			}
		}

		static void DeleteInstance()
		{
			delete m_instance;
			m_instance = nullptr;
		}

		static PostEffectManager* GetInstance() { return m_instance; }

		/// <summary>
		/// �e��ݒ���I���ɂ��邩�ǂ�������́A���݂̓u���[���̂݁B
		/// </summary>
		/// <param name="bloomMode">�u���[�����I���ɂ��邩?</param>
		void Init(bool bloomMode, bool shadowMode);

		bool GetShadowFlag()
		{
			return m_shadowMode;
		}

		Texture& GetShadowMap()
		{
			return m_shadowMap.GetRenderTargetTexture();
		}

		Texture& GetBlurShadowMap()
		{
			return m_shadowBlur.GetBokeTexture();
		}

		/// <summary>
		/// �����_�����O�O�̏���
		/// </summary>
		void BeforeRender(RenderContext& rc);

		/// <summary>
		/// �����_�����O��̏���
		/// </summary>
		/// <param name="rc"></param>
		void AfterRender(RenderContext& rc);

		void ShadowRender(RenderContext& rc);

		void EndShadowRender(RenderContext& rc);
	private:
		RenderTarget m_mainRenderTarget;
		Sprite m_copyToFrameBufferSprite;//��ʂɕ\������ŏI���ʂ̃X�v���C�g�B

		//�u���[���֘A�B
		bool m_bloomMode = true; //�u���[�����L����
		RenderTarget m_luminnceRenderTarget;
		Sprite m_luminanceSprite;//�P�x���o�����X�v���C�g�B
		Sprite m_bokeLuminanceSprite;//�P�x���o�������̂Ƀu���[���������X�v���C�g�B
		GaussianBlur m_gaussianBlur[4];//�u���[�B

		bool m_shadowMode = true;//�V���h�E���L�����B
		RenderTarget m_shadowMap;
		GaussianBlur m_shadowBlur;
	};

}