#pragma once

#include "SceneObjectImpl.h"

class Sphere : public SceneObjectImpl
{
public:
	Sphere(float radius);

private:
	// Inherited via ISceneObject
	virtual bool Hit(const Ray& ray, HitPayload& payload) const override;

	float m_radius;
};
