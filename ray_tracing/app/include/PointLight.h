#pragma once

#include <glm/glm.hpp>

class PointLight
{
public:
	glm::vec3 Position;
	float Intensity;
	glm::vec3 LightColor;
};
