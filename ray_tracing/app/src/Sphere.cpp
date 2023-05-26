#include "Sphere.h"

bool Sphere::Hit(const Ray& actualRay, HitPayload& payload) const
{
	Ray ray = actualRay;
	ray.Transform(GetInverseTransform());

	const float r = 1.0f;
	float a = glm::dot(ray.Direction, ray.Direction);
	float b = 2.0f * glm::dot(ray.Origin, ray.Direction);
	float c = glm::dot(ray.Origin, ray.Origin) - r * r;

	float discriminant = b * b - 4.0f * a * c;

	if (discriminant < 0.0f)
		return false; // No intersections

	float lowestTime = (-b - glm::sqrt(discriminant)) / (2.0f * a);
	if (lowestTime > 0.0f && lowestTime < payload.HitTime)
	{
		payload.HitTime = lowestTime;
		payload.WorldNormal = ray.At(lowestTime);
		return true; // New closest hit found
	}

	return false; // Found hit isn't closest
}
