#include "stdafx.h"
#include "FontRender.h"
void FontRender::Render(RenderContext& rc, Camera* camera)
{
	if (rc.GetRenderStep() == RenderContext::eStep_Render)
	{
		m_PosX_font.Begin(rc);
		m_PosX_font.Draw(m_text.c_str(), m_position, m_color, m_rotation, m_scale, m_pivot);
		m_PosX_font.End(rc);
	}
}