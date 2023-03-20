#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "glad_glfw.h"

#include <functional>
#include <stdexcept>

#include "Config.h"
#include "controller/GlfwCallbacks.h"

class BaseGlfwWindow
{
public:

	BaseGlfwWindow(int width, int height, const char* title);
	~BaseGlfwWindow();

	void Run();

protected:

	void SetKeyCallback(GlfwKeyCallback&& callback);
	void SetCursorPosCallback(GlfwCursorPosCallback&& callback);
	void SetMouseButtonCallback(GlfwMouseButtonCallback&& callback);

private:

	virtual void Draw(int width, int height) = 0;

	void InitGraphics();

	GLFWwindow* m_window;

	GlfwKeyCallback m_keyCallback;
	GlfwCursorPosCallback m_cursorPosCallback;
	GlfwMouseButtonCallback m_mouseButtonCallback;
};
