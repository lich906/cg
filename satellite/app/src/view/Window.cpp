#include "view/Window.h"

void Window::SetController(std::unique_ptr<WindowController>&& controller)
{
	m_controller = std::move(controller);
	SetKeyCallback(m_controller->GetKeyCallback());
	SetCursorPosCallback(m_controller->GetCursorPosCallback());
	SetMouseButtonCallback(m_controller->GetMouseButtonCallback());
}

void Window::Draw(int width, int height)
{
	m_controller->Draw(width, height);
}
