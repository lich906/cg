#pragma once

#include "glm/glm.hpp"

struct IImageObjectObserver
{
	virtual ~IImageObjectObserver() = default;

	virtual void UpdateTransformMatrix(const glm::mat4&) = 0;
};
