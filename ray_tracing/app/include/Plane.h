#pragma once

#include "SceneObjectImpl.h"

class Plane : public SceneObjectImpl
{
public:
	Plane(const glm::vec3& normal);

private:
	// Inherited via ISceneObject
	virtual bool Hit(const Ray& ray, HitPayload& payload) const override;

	glm::vec3 m_normal;
};
