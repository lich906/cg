#pragma once

#include <glad/glad.h>

struct Color
{
	static constexpr GLint Size = 4;

	GLfloat r, g, b, a;
};
