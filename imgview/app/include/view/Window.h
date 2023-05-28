#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "graphics/CurrentProgram.h"
#include "glm/glm.hpp"

#include "MainMenu.h"
#include "IMouseInputController.h"
#include "Scene.h"
#include <GLFW/glfw3.h>

class Window
{
public:
	Window(const std::shared_ptr<Scene>& scene,
		const std::shared_ptr<IMouseInputController>& mouseInputController,
		const std::shared_ptr<IMenuController>& menuController);
	~Window();

	void Run();

private:
	void Draw();
	bool InitGraphics();
	void SetupInputCallbacks();
	void UpdateProjectionMatrixAndViewport();

	struct Color
	{
		float r, g, b, a;
	} m_clearColor;

	GLFWwindow* m_window;

	MainMenu m_mainMenu;

	std::shared_ptr<Scene> m_scene;
	std::shared_ptr<IMouseInputController> m_mouseInputController;
	glm::vec2 m_lastCursorPos;
};
