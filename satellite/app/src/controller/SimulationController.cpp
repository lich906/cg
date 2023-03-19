#include "controller/SimulationController.h"
#include "controller/SetupController.h"

void SimulationController::Draw(int width, int height)
{
	m_viewModel.Draw(width, height);
	m_model.NextState(config::Timestep);
}

GlfwMouseButtonCallback SimulationController::GetMouseButtonCallback()
{
	return [this](GLFWwindow* window, int button, int action, int mods) -> void {};
}

GlfwCursorPosCallback SimulationController::GetCursorPosCallback()
{
	return [this](GLFWwindow* window, double xpos, double ypos) -> void {};
}

GlfwKeyCallback SimulationController::GetKeyCallback()
{
	return [this](GLFWwindow* window, int key, int scancode, int action, int mods) -> void {
		if (key == GLFW_KEY_BACKSPACE && action == GLFW_RELEASE)
		{
			int w, h;
			glfwGetFramebufferSize(window, &w, &h);
			m_window->SetController(std::make_unique<SetupController>(m_model, m_viewModel, m_window, w, h));
		}
	};
}
