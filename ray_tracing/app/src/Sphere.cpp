#include "Sphere.h"

std::optional<float> Sphere::FindLowestHitTime(const Ray& ray) const
{
	const float a = glm::dot(ray.Direction, ray.Direction);
	const float b = glm::dot(ray.Origin, ray.Direction);
	const float c = glm::dot(ray.Origin, ray.Origin) - 1.0f;

	const float discriminant = b * b - a * c;

	if (discriminant < 0.0f)
		return std::nullopt; // No intersections

	const float sqrtD = glm::sqrt(discriminant);
	const float t0 = (-b - sqrtD) / a;
	const float t1 = (-b + sqrtD) / a;
	const float time = t0 < t1 ? (t0 > 0.0f ? t0 : t1) : (t1 > 0.0f ? t1 : t0);

	return time;
}

glm::vec3 Sphere::GetNormalInLocalSpace(const glm::vec3& point) const
{
	return point;
}
