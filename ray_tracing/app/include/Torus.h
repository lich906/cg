#pragma once

#include "AbstractSceneObject.h"

class Torus : public AbstractSceneObject
{
public:
	Torus(float R, float r);

private:
	// Inherited via AbstractSceneObject
	virtual std::optional<float> FindLowestHitTime(const Ray& ray) const override;
	virtual glm::vec3 GetNormalInLocalSpace(const glm::vec3& point) const override;

	float m_R, m_r;
};
