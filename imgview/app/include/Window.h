#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "glad_glfw.h"
#include "graphics/CurrentShader.h"
#include "glm/glm.hpp"

#include "MainMenu.h"
#include "IMouseInputController.h"

class Window
{
public:
	Window(const std::shared_ptr<IMouseInputController>& mouseInputController,
		const std::shared_ptr<IMenuController>& menuController);
	~Window();

	void Run();

private:
	void Render();

	bool InitGraphics();

	struct Color
	{
		float r, g, b, a;
	} m_clearColor;

	GLFWwindow* m_window;

	MainMenu m_mainMenu;
};
