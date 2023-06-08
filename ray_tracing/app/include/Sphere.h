#pragma once

#include "AbstractSceneObject.h"

class Sphere : public AbstractSceneObject
{
private:
	// Inherited via AbstractSceneObject
	virtual std::optional<float> FindLowestHitTime(const Ray& ray) const override;
	virtual glm::vec3 GetNormalInLocalSpace(const glm::vec3& point) const override;
};
