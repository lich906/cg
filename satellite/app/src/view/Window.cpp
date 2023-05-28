#include "view/Window.h"
#include "controller/SetupController.h"
#include "controller/SimulationController.h"
#include "controller/NoObjectsLeftController.h"

Window::Window(GLFWwindow* window, UniverseModel& model, Scene& scene)
	: BaseGlfwWindow(window)
	, m_scene(scene)
	, m_model(model)
	, m_menuWindow(this)
{
	InitControllers();
	SetController(ControllerType::Setup);

	SetMouseButtonCallback(
		[this](GLFWwindow* window, int button, int action, int mods) -> void {
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		glm::vec2 cursorPos = GetCursorPosInWorld(x, y);

		if (button == GLFW_MOUSE_BUTTON_LEFT)
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

		if (button == GLFW_MOUSE_BUTTON_RIGHT)
		{
			if (action == GLFW_PRESS)
			{
				m_movingCamera = true;
			}
			if (action == GLFW_RELEASE)
			{
				m_movingCamera = false;
			}
		}
	});

	SetCursorPosCallback(
		[this, prevCursorPos = glm::vec2()]
	(GLFWwindow* window, double xpos, double ypos) mutable -> void {
			glm::vec2 cursorPos(static_cast<float>(xpos), static_cast<float>(ypos));
			glm::vec2 delta = cursorPos - prevCursorPos;
			if (m_movingCamera)
				m_camera.OnCameraMove(delta);
			m_controller->OnMouseMove(cursorPos - Camera::GetOffset(), delta);
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
	Camera::UpdateViewMatrix();
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
	m_controllers.insert({ ControllerType::NoObjectsLeft, std::make_unique<NoObjectsLeftController>(static_cast<IWindowContext*>(this)) });
}

glm::vec2 Window::GetCursorPosInWorld(double x, double y)
{
	glm::vec2 actualPos(static_cast<float>(x), static_cast<float>(y));

	return actualPos - Camera::GetOffset();
}

void Window::CloseWindow()
{
	BaseGlfwWindow::CloseWindow();
}
