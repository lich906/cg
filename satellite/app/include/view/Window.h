#pragma once

#include <memory>

#include "BaseGlfwWindow.h"
#include "controller/IController.h"
#include "view/MenuWindow.h"

class Window : public BaseGlfwWindow, public IControllableWindow
{
public:
	Window(GLFWwindow* window, Scene& scene, MenuWindow& menuW);

	void SetController(std::unique_ptr<IController>&& controller) override;

private:

	void Draw(int width, int height) override;

	std::unique_ptr<IController> m_controller;
	Scene& m_scene;
	MenuWindow& m_menuWindow;
};
