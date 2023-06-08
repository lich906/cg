#pragma once

#include "AbstractSceneObject.h"

class Plane : public AbstractSceneObject
{
public:
	Plane(const glm::vec3& normal);

private:
	// Inherited via AbstractSceneObject
	virtual std::optional<float> FindLowestHitTime(const Ray& ray) const override;
	virtual glm::vec3 GetNormalInLocalSpace(const glm::vec3& point) const override;

	glm::vec3 m_normal;
};
