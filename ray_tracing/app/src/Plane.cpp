#include "Plane.h"

Plane::Plane(const glm::vec3& normal)
	: m_normal(normal)
{
}

bool Plane::Hit(const Ray& actualRay, HitPayload& payload) const
{
	Ray ray = actualRay;
	ray.Transform(GetInverseTransform());

	float time = -(glm::dot(m_normal, ray.Origin) / glm::dot(m_normal, ray.Direction));

	if (time > 0.0f && time < payload.HitTime)
	{
		payload.HitTime = time;
		payload.WorldNormal = m_normal;
		return true; // New closest hit found
	}

	return false; // Found hit isn't closest
}
