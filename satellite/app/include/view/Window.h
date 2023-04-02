#pragma once

#include <memory>
#include <unordered_map>

#include "BaseGlfwWindow.h"
#include "controller/IWindowContext.h"
#include "controller/AbstractController.h"
#include "view/MenuWindow.h"

class Window : public BaseGlfwWindow, private IWindowContext
{
public:
	Window(GLFWwindow* window, UniverseModel& model, Scene& scene);

private:
	// Inherited via BaseGlfwWindow
	virtual void Draw(int width, int height) override;

	// Inherited via IWindowContext
	virtual void SetController(ControllerType) override;
	virtual UniverseModel& GetModel() override;
	virtual Scene& GetScene() override;
	virtual MenuWindow& GetMenuWindow() override;

	void InitControllers();

	AbstractController* m_controller;
	std::unordered_map<ControllerType, std::unique_ptr<AbstractController>> m_controllers;

	Scene& m_scene;
	UniverseModel& m_model;
	MenuWindow m_menuWindow;
};
