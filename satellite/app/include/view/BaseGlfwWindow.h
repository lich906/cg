#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <functional>
#include <stdexcept>

#include "Config.h"
#include "controller/GlfwCallbacks.h"
#include "graphics/CurrentProgram.h"

#include <GLFW/glfw3.h>

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

	virtual void Draw() = 0;

	bool InitGraphicsContext(int width, int height, const char* title);
	void UpdateProjectionMatrixAndViewport();

	GLFWwindow* m_window;

	GlfwKeyCallback m_keyCallback;
	GlfwCursorPosCallback m_cursorPosCallback;
	GlfwMouseButtonCallback m_mouseButtonCallback;
};
