#pragma once

#include <glm/glm.hpp>

struct HitPayload
{
	float HitTime;
	glm::vec3 WorldPosition;
	glm::vec3 WorldNormal;
	int ObjectIndex;
};
