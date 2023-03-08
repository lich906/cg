#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

class GlfwInitializer final
{
public:
	GlfwInitializer();

	GlfwInitializer(const GlfwInitializer&) = delete;
	GlfwInitializer& operator=(const GlfwInitializer&) = delete;

	~GlfwInitializer();
};
