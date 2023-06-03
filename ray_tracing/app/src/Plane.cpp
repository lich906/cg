#include "Plane.h"

Plane::Plane(const glm::vec3& normal)
	: m_normal(normal)
{
}

bool Plane::Hit(const Ray& worldRay, HitPayload& payload) const
{
	Ray ray(worldRay, GetInverseTransform());

	float time = -(glm::dot(m_normal, ray.Origin) / glm::dot(m_normal, ray.Direction));

	if (time > TIME_EPSILON && time < payload.HitTime)
	{
		payload.HitTime = time;
		payload.WorldNormal = m_normal;
		return true; // New closest hit found
	}

	return false; // Found hit isn't closest
}
