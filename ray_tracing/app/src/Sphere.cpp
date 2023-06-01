#include "Sphere.h"

bool Sphere::Hit(const Ray& actualRay, HitPayload& payload) const
{
	Ray ray = actualRay;
	ray.Origin += ray.Direction * TIME_EPSILON;
	ray.Transform(GetInverseTransform());

	const float r = 1.0f;
	float a = glm::dot(ray.Direction, ray.Direction);
	float b = 2.0f * glm::dot(ray.Origin, ray.Direction);
	float c = glm::dot(ray.Origin, ray.Origin) - r * r;

	float discriminant = b * b - 4.0f * a * c;

	if (discriminant < 0.0f)
		return false; // No intersections

	float sqrtD = glm::sqrt(discriminant);
	float t0 = (-b - sqrtD) / (2.0f * a);
	float t1 = (-b + sqrtD) / (2.0f * a);
	float time = t0 < t1 ? (t0 > 0.0f ? t0 : t1) : (t1 > 0.0f ? t1 : t0);

	if (time > TIME_EPSILON && time < payload.HitTime)
	{
		payload.HitTime = time;
		payload.WorldNormal = glm::normalize(GetNormalMatrix() * ray.At(time));
		return true; // New closest hit found
	}

	return false; // Found hit isn't closest
}
