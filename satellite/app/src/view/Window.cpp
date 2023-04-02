#include "view/Window.h"
#include "controller/SetupController.h"
#include "controller/SimulationController.h"

Window::Window(GLFWwindow* window, UniverseModel& model, Scene& scene)
	: BaseGlfwWindow(window)
	, m_scene(scene)
	, m_model(model)
	, m_menuWindow(model)
{
	InitControllers();
	SetController(ControllerType::Setup);

	SetMouseButtonCallback(
		[this](GLFWwindow* window, int button, int action, int mods) -> void {
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		gfx::Vector cursorPos(static_cast<float>(x), static_cast<float>(y));

		if ((button == GLFW_MOUSE_BUTTON_LEFT || button == GLFW_MOUSE_BUTTON_RIGHT))
		{
			if (action == GLFW_PRESS)
			{
				m_controller->OnMouseDown(cursorPos, mods);
			}
			if (action == GLFW_RELEASE)
			{
				m_controller->OnMouseUp(cursorPos);
			}
		}
	});

	SetCursorPosCallback(
		[this, prevCursorPos = gfx::Vector()]
		(GLFWwindow* window, double xpos, double ypos) mutable -> void {
			gfx::Vector cursorPos{ static_cast<float>(xpos), static_cast<float>(ypos) };

			m_controller->OnMouseMove(cursorPos, cursorPos - prevCursorPos);
			prevCursorPos = cursorPos;
		});

	SetKeyCallback([this](GLFWwindow* window, int key, int scancode, int action, int mods) -> void {
		if (action == GLFW_PRESS)
		{
			m_controller->OnKeyPress(key);
		}
	});
}

void Window::Draw(int width, int height)
{
	m_controller->OnIdle();
	m_scene.Update(config::Timestep);
	m_scene.Draw(width, height);
	m_menuWindow.Draw();
}

void Window::SetController(ControllerType type)
{
	m_controller = m_controllers[type].get();
	m_controller->OnSet();
}

UniverseModel& Window::GetModel()
{
	return m_model;
}

Scene& Window::GetScene()
{
	return m_scene;
}

MenuWindow& Window::GetMenuWindow()
{
	return m_menuWindow;
}

void Window::InitControllers()
{
	m_controllers.insert({ ControllerType::Setup, std::make_unique<SetupController>(static_cast<IWindowContext*>(this)) });
	m_controllers.insert({ ControllerType::Simulation, std::make_unique<SimulationController>(static_cast<IWindowContext*>(this)) });
}
