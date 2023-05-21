#include "SceneObjectImpl.h"

glm::mat4 SceneObjectImpl::GetInverseTransform() const
{
	return m_inverseTransform;
}

void SceneObjectImpl::SetMaterial(const Material& material)
{
	m_material = material;
}

Material SceneObjectImpl::GetMaterial() const
{
	return m_material;
}

void SceneObjectImpl::SetTransform(const glm::mat4& transformMat)
{
	m_transform = transformMat;
	m_inverseTransform = glm::inverse(m_transform);
	OnTransformUpdate(m_transform);
}

glm::mat4 SceneObjectImpl::GetTransform() const
{
	return m_transform;
}
