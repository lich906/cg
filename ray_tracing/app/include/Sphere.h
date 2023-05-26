#pragma once

#include "SceneObjectImpl.h"

class Sphere : public SceneObjectImpl
{
public:
	Sphere() = default;

private:
	// Inherited via ISceneObject
	virtual bool Hit(const Ray& ray, HitPayload& payload) const override;
};
