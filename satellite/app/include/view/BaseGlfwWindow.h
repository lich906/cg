#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <functional>
#include <stdexcept>

class BaseGlfwWindow
{
public:
	using KeyCallback = std::function<void(GLFWwindow* window, int key, int scancode, int action, int mods)>;
	using CursorPosCallback = std::function<void(GLFWwindow* window, double xpos, double ypos)>;
	using MouseButtonCallback = std::function<void(GLFWwindow* window, int button, int action, int mods)>;

	BaseGlfwWindow(int width, int height, const char* title);
	~BaseGlfwWindow();

	void Run();

protected:

	void SetKeyCallback(KeyCallback callback);
	void SetCursorPosCallback(CursorPosCallback callback);
	void SetMouseButtonCallback(MouseButtonCallback callback);

private:

	virtual void Draw(int width, int height) = 0;

	GLFWwindow* CreateGlfwWindow(int width, int height, const char* title);

	GLFWwindow* m_window;

	BaseGlfwWindow* m_myWindowPointer;

	KeyCallback m_keyCallback;
	CursorPosCallback m_cursorPosCallback;
	MouseButtonCallback m_mouseButtonCallback;

	static void InvokeKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void InvokeCursorPosCallback(GLFWwindow* window, double xpos, double ypos);
	static void InvokeMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
};
