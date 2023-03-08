#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

class BaseGlfwWindow
{
public:
	BaseGlfwWindow(int w, int h, const char* title);

	BaseGlfwWindow(const BaseGlfwWindow&) = delete;
	BaseGlfwWindow& operator=(const BaseGlfwWindow&) = delete;

	virtual ~BaseGlfwWindow();

	void Run();

private:
	virtual void Draw(int width, int height) = 0;

	static GLFWwindow* CreateWindow(int w, int h, const char* title);

	GLFWwindow* m_window;
};
