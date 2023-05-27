#pragma once

#include "SceneObjectImpl.h"

class Torus : public SceneObjectImpl
{
public:
	Torus(float R, float r);

private:
	// Inherited via ISceneObject
	virtual bool Hit(const Ray& ray, HitPayload& payload) const override;

	glm::vec3 GetNormal(const glm::vec3& p) const;

	float m_R, m_r;
};
