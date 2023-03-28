#include "view/Window.h"

Window::Window(int width, int height, const char* title)
	: BaseGlfwWindow(width, height, title)
{
	SetMouseButtonCallback(
		[this](GLFWwindow* window, int button, int action, int mods) -> void {
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		gfx::Vector cursorPos{ static_cast<float>(x), static_cast<float>(y) };

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

void Window::SetController(std::unique_ptr<IController>&& controller)
{
	m_controller = std::move(controller);
}

void Window::Draw(int width, int height)
{
	m_controller->OnDraw(width, height);
}
