#pragma once

#include <optional>

#include "ISceneObject.h"

constexpr float TIME_EPSILON = 0.005f;

class AbstractSceneObject : public ISceneObject
{
public:
	// Inherited via ISceneObject
	virtual bool Hit(const Ray& ray, HitPayload& payload) const override;
	virtual void SetMaterial(const Material& material) override;
	virtual Material GetMaterial() const override;
	virtual void SetTransform(const glm::mat4& transformMat) override;
	virtual glm::mat4 GetTransform() const override;
	virtual glm::mat4 GetInverseTransform() const override;

private:
	glm::vec3 CalculateNormal(const glm::vec3& point) const;

	virtual std::optional<float> FindLowestHitTime(const Ray& ray) const = 0;
	virtual glm::vec3 GetNormalInLocalSpace(const glm::vec3& point) const = 0;

	Material m_material;
	glm::mat4 m_transform{ 1.0f };
	glm::mat4 m_inverseTransform{ 1.0f };
	glm::mat3 m_normalMatrix{ 1.0f };
};
