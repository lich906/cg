#pragma once

#include <glm/glm.hpp>

class Ray
{
public:
	glm::vec3 Origin;
	glm::vec3 Direction;

	glm::vec3 At(float t) const;
	void Transform(const glm::mat4& tm);

private:
	glm::vec4 Project(const glm::vec4& vec) const;
};
