#include "Background.h"

Background::Background(const glm::vec4& color)
	: m_color(color)
{
}

void Background::OnDraw(gfx::Program& prog)
{
	GlCall(glClearColor(m_color.r, m_color.g, m_color.b, m_color.a));
	GlCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}
