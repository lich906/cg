#include "view/BaseGlfwWindow.h"

BaseGlfwWindow::BaseGlfwWindow(int width, int height, const char* title)
	: m_window(CreateGlfwWindow(width, height, title))
{
	if (!m_window)
	{
		throw std::runtime_error("Failed to create window");
	}

	glfwSetWindowUserPointer(m_window, m_myWindowPointer);

	glfwSetKeyCallback(m_window, InvokeKeyCallback);
	glfwSetCursorPosCallback(m_window, InvokeCursorPosCallback);
	glfwSetMouseButtonCallback(m_window, InvokeMouseButtonCallback);
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
		glfwPollEvents();

		int width, height;
		glfwGetFramebufferSize(m_window, &width, &height);
		Draw(width, height);

		glfwSwapBuffers(m_window);
	}
}

void BaseGlfwWindow::SetKeyCallback(KeyCallback callback)
{
	m_keyCallback = callback;
}

void BaseGlfwWindow::SetCursorPosCallback(CursorPosCallback callback)
{
	m_cursorPosCallback = callback;
}

void BaseGlfwWindow::SetMouseButtonCallback(MouseButtonCallback callback)
{
	m_mouseButtonCallback = callback;
}

GLFWwindow* BaseGlfwWindow::CreateGlfwWindow(int width, int height, const char* title)
{
	return glfwCreateWindow(width, height, title, nullptr, nullptr);
}

void BaseGlfwWindow::InvokeKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	static_cast<BaseGlfwWindow*>(glfwGetWindowUserPointer(window))->m_keyCallback(window, key, scancode, action, mods);
}

void BaseGlfwWindow::InvokeCursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	static_cast<BaseGlfwWindow*>(glfwGetWindowUserPointer(window))->m_cursorPosCallback(window, xpos, ypos);
}

void BaseGlfwWindow::InvokeMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	static_cast<BaseGlfwWindow*>(glfwGetWindowUserPointer(window))->m_mouseButtonCallback(window, button, action, mods);
}
