#include "opengl_abstractions/CurrentShader.h"

void CurrentShader::Set(Shader&& shader)
{
	m_shader = std::move(shader);
}

Shader& CurrentShader::Get()
{
	if (m_shader)
	{
		return *m_shader;
	}

	throw std::logic_error("Current shader was not set.");
}
