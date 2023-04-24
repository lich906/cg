#pragma once

#include "glm/glm.hpp"
#include "graphics/Program.h"

class LightSource
{
public:
	LightSource();

	void Use(gfx::Program& program);
	void SetPosition(const glm::vec3& p) { m_position = p; }
	void SetLightColor(const glm::vec4& c) { m_lightColor = c; }

private:
	glm::vec3 m_position;
	glm::vec4 m_lightColor;
};
