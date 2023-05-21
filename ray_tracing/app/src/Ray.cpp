#include "Ray.h"

glm::vec3 Ray::At(float t) const
{
	return Origin + Direction * t;
}

void Ray::Transform(const glm::mat4& tm)
{
	Origin = Project(tm * glm::vec4(Origin, 1.0f));
	Direction = tm * glm::vec4(Direction, 0.0f);
}

glm::vec4 Ray::Project(const glm::vec4& vec) const
{
	return vec / vec.w;
}
