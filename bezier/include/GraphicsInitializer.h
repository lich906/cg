#pragma once

#include "common.h"
#include <GLFW/glfw3.h>

class GraphicsInitializer
{
public:
	GraphicsInitializer(int width, int height, const char* title);
	~GraphicsInitializer() noexcept;

	GLFWwindow* GetGLFWwindow() const;

private:
	GLFWwindow* m_window;
};
