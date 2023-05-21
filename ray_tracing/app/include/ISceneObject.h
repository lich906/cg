#pragma once

#include "Ray.h"
#include "HitPayload.h"
#include "Material.h"

struct ISceneObject
{
	virtual ~ISceneObject() = default;
	/*
		Return 'true' if found hit is closest.
	*/
	virtual bool Hit(const Ray& ray, HitPayload& payload) const = 0;
	virtual void SetMaterial(const Material& material) = 0;
	virtual Material GetMaterial() const = 0;
	virtual void SetTransform(const glm::mat4& transformMat) = 0;
	virtual glm::mat4 GetInverseTransform() const = 0;
	virtual glm::mat4 GetTransform() const = 0;
};
