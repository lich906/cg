#include "Sphere.h"

bool Sphere::Hit(const Ray& worldRay, HitPayload& payload) const
{
	Ray ray(worldRay, GetInverseTransform());
	ray.Origin += ray.Direction * TIME_EPSILON;

	const float r = 1.0f;
	const float a = glm::dot(ray.Direction, ray.Direction);
	const float b = glm::dot(ray.Origin, ray.Direction);
	const float c = glm::dot(ray.Origin, ray.Origin) - r * r;

	const float discriminant = b * b - a * c;

	if (discriminant < 0.0f)
		return false; // No intersections

	const float sqrtD = glm::sqrt(discriminant);
	const float t0 = (-b - sqrtD) / a;
	const float t1 = (-b + sqrtD) / a;
	const float time = t0 < t1 ? (t0 > 0.0f ? t0 : t1) : (t1 > 0.0f ? t1 : t0);

	if (time > TIME_EPSILON && time < payload.HitTime)
	{
		payload.HitTime = time;
		payload.WorldNormal = glm::normalize(GetNormalMatrix() * ray.At(time));
		return true; // New closest hit found
	}

	return false; // Found hit isn't closest
}
