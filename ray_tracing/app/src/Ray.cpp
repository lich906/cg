#include "Ray.h"

Ray::Ray(const Ray& ray, const glm::mat4& transform)
	: Origin(transform * glm::vec4(ray.Origin, 1.0f))
	, Direction(transform * glm::vec4(ray.Direction, 0.0f))
{
}

glm::vec3 Ray::At(float t) const
{
	return Origin + Direction * t;
}
