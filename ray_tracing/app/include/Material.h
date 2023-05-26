#pragma once

#include <glm/glm.hpp>

struct Material
{
	Material(
		const glm::vec3& color = glm::vec3(1.0f),
		float roughness = 1.0f,
		float metallic = 0.0f)
		: Color(color)
		, Roughness(roughness)
		, Metallic(metallic)
	{
	}

	glm::vec3 Color;
	float Roughness;
	float Metallic;
};
