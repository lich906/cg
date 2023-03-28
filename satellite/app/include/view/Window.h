#pragma once

#include <memory>

#include "BaseGlfwWindow.h"
#include "controller/IController.h"

class Window : public BaseGlfwWindow, public IControllableWindow
{
public:
	Window(int width, int height, const char* title);

	void SetController(std::unique_ptr<IController>&& controller) override;

private:

	void Draw(int width, int height) override;

	std::unique_ptr<IController> m_controller;
};
