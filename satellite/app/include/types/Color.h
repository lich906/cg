#pragma once

#include "glad_glfw.h"

struct Color
{
	static constexpr GLint Size = 4;

	GLfloat r, g, b, a;
};
