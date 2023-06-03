#pragma once

#include <glm/glm.hpp>

class Ray
{
public:
	Ray() = default;
	Ray(const Ray& ray, const glm::mat4& transform);

	glm::vec3 Origin;
	glm::vec3 Direction;

	glm::vec3 At(float t) const;
};
