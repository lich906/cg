#include "Sphere.h"

Sphere::Sphere(float radius)
	: m_radius(radius)
{
}

bool Sphere::Hit(const Ray& actualRay, HitPayload& payload) const
{
	Ray ray = actualRay;
	ray.Transform(GetInverseTransform());

	float a = glm::dot(ray.Direction, ray.Direction);
	float b = 2.0f * glm::dot(ray.Origin, ray.Direction);
	float c = glm::dot(ray.Origin, ray.Origin) - m_radius * m_radius;

	float discriminant = b * b - 4.0f * a * c;

	if (discriminant < 0.0f)
		return false; // No intersections

	float lowestTime = (-b - glm::sqrt(discriminant)) / (2.0f * a);
	if (lowestTime > 0.0f && lowestTime < payload.HitTime)
	{
		payload.HitTime = lowestTime;
		return true; // New closest hit found
	}

	return false; // Found hit isn't closest
}
