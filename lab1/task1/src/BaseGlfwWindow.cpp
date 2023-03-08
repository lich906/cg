#include "BaseGlfwWindow.h"

BaseGlfwWindow::BaseGlfwWindow(int w, int h, const char* title)
	: m_window{ CreateWindow(w, h, title) }
{
	if (!m_window)
	{
		throw std::runtime_error("Failed to create window");
	}
}

BaseGlfwWindow::~BaseGlfwWindow()
{
	glfwDestroyWindow(m_window);
}

void BaseGlfwWindow::Run()
{
	glfwMakeContextCurrent(m_window);
	gladLoadGL();
	while (!glfwWindowShouldClose(m_window))
	{
		int w, h;
		glfwGetFramebufferSize(m_window, &w, &h);
		Draw(w, h);
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
}

GLFWwindow* BaseGlfwWindow::CreateWindow(int w, int h, const char* title)
{
	return glfwCreateWindow(w, h, title, nullptr, nullptr);
}