#include "AbstractSceneObject.h"

bool AbstractSceneObject::Hit(const Ray& ray, HitPayload& payload) const
{
	Ray localRay(ray, GetInverseTransform());
	localRay.Origin += localRay.Direction * TIME_EPSILON;

	auto time = FindLowestHitTime(localRay);

	if (time && *time > TIME_EPSILON && *time < payload.HitTime)
	{
		payload.HitTime = *time;
		payload.WorldNormal = CalculateNormal(localRay.At(*time));
		return true; // New closest hit found
	}

	return false;
}

glm::mat4 AbstractSceneObject::GetInverseTransform() const
{
	return m_inverseTransform;
}

glm::vec3 AbstractSceneObject::CalculateNormal(const glm::vec3& point) const
{
	return glm::normalize(glm::mat3(glm::transpose(GetInverseTransform())) * GetNormalInLocalSpace(point));
}

void AbstractSceneObject::SetMaterial(const Material& material)
{
	m_material = material;
}

Material AbstractSceneObject::GetMaterial() const
{
	return m_material;
}

void AbstractSceneObject::SetTransform(const glm::mat4& transformMat)
{
	m_transform = transformMat;
	m_inverseTransform = glm::inverse(m_transform);
}

glm::mat4 AbstractSceneObject::GetTransform() const
{
	return m_transform;
}
