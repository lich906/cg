#include "Plane.h"

Plane::Plane(const glm::vec3& normal)
	: m_normal(normal)
{
}

std::optional<float> Plane::FindLowestHitTime(const Ray& ray) const
{
	return -(glm::dot(m_normal, ray.Origin) / glm::dot(m_normal, ray.Direction));
}

glm::vec3 Plane::GetNormalInLocalSpace(const glm::vec3&) const
{
	return m_normal;
}
