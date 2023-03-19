#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "glad_glfw.h"

#include <functional>
#include <stdexcept>

#include "Config.h"
#include "controller/GlfwCallbacks.h"
#include "opengl_abstractions/Shader.h"

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

	Shader& GetShaderRef();

private:

	virtual void Draw(int width, int height) = 0;

	void SetupProjectionMatrix(int width, int height);

	Shader InitGraphics();

	GLFWwindow* CreateGlfwWindow(int width, int height, const char* title);

	GLFWwindow* m_window;

	GlfwKeyCallback m_keyCallback;
	GlfwCursorPosCallback m_cursorPosCallback;
	GlfwMouseButtonCallback m_mouseButtonCallback;

	Shader m_shader;

	static void InvokeKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void InvokeCursorPosCallback(GLFWwindow* window, double xpos, double ypos);
	static void InvokeMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
};
