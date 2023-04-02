#pragma once

#include <functional>

#include "glm/ext/matrix_float4x4.hpp"
#include "graphics/CurrentProgram.h"

class SceneObject
{
public:
	using RemoveCallback = std::function<void(const SceneObject*)>;

	SceneObject();

	void SetRemoveCallback(const RemoveCallback& deleter);

	void Draw(int width, int height);

protected:

	void RemoveSelf();

	virtual void DoDraw(int width, int height) = 0;

	void Transform(const glm::mat4& mat);

private:
	glm::mat4 m_transformMat;

	RemoveCallback m_removeCallback;
};
