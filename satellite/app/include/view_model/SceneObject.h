#pragma once

#include <functional>

#include "glm/ext/matrix_float4x4.hpp"
#include "graphics/CurrentProgram.h"

class SceneObject
{
public:
	using ObjectDeleter = std::function<void(const SceneObject*)>;

	SceneObject();

	void SetDeleter(const ObjectDeleter& deleter);

	void Draw();

protected:

	void DestroySelf();

	virtual void DoDraw() = 0;

	void Transform(const glm::mat4& mat);

private:
	glm::mat4 m_transformMat;

	ObjectDeleter m_deleter;
};
