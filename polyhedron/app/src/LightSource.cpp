#include "LightSource.h"

LightSource::LightSource()
	: m_lightColor()
	, m_position()
{
}

void LightSource::Use(gfx::Program& program)
{
	program.SetUniform3fv("u_lightPosition", m_position);
	program.SetUniform4fv("u_lightColor", m_lightColor);
}
