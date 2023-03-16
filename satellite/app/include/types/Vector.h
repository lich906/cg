#pragma once

#include "glad_glfw.h"

struct Vector
{
	constexpr Vector(float x_ = 0.0f, float y_ = 0.0f)
		: x(x_)
		, y(y_)
	{
	}

	static constexpr GLint Size = 2;

	GLfloat x, y;
};
