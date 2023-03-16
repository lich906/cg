#pragma once

#include <memory>

#include "BaseGlfwWindow.h"
#include "controller/WindowController.h"
#include "opengl_abstractions/Shader.h"

class Window : public BaseGlfwWindow, public IControllableWindow
{
public:

	using BaseGlfwWindow::BaseGlfwWindow;

	void SetController(std::unique_ptr<WindowController>&& controller) override;

private:

	void Draw(int width, int height) override;

	std::unique_ptr<WindowController> m_controller;
};
