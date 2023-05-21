#pragma once

#include "ISceneObject.h"

class SceneObjectImpl : public ISceneObject
{
public:
	// Inherited via ISceneObject
	virtual void SetMaterial(const Material& material) override;
	virtual Material GetMaterial() const override;
	virtual void SetTransform(const glm::mat4& transformMat) override;
	virtual glm::mat4 GetTransform() const override;
	virtual glm::mat4 GetInverseTransform() const override;

protected:
	virtual void OnTransformUpdate(const glm::mat4& transformMat) {};

private:
	Material m_material;
	glm::mat4 m_transform{ 1.0f };
	glm::mat4 m_inverseTransform{ 1.0f };
};
