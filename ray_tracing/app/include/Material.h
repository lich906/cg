#pragma once

#include <glm/glm.hpp>

struct Material
{
	glm::vec3 Color = glm::vec3(1.0f);
	float Roughness = 1.0f;
	float Metallic = 0.0f;
};
