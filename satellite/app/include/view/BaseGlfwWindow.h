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

	BaseGlfwWindow(GLFWwindow* window);
	~BaseGlfwWindow();

	void Run();

protected:

	void SetKeyCallback(GlfwKeyCallback&& callback);
	void SetCursorPosCallback(GlfwCursorPosCallback&& callback);
	void SetMouseButtonCallback(GlfwMouseButtonCallback&& callback);

	void CloseWindow();

private:

	virtual void Draw(int width, int height) = 0;

	bool InitGraphicsContext();
	void UpdateProjectionMatrixAndViewport();

	GLFWwindow* m_window;

	GlfwKeyCallback m_keyCallback;
	GlfwCursorPosCallback m_cursorPosCallback;
	GlfwMouseButtonCallback m_mouseButtonCallback;
};
