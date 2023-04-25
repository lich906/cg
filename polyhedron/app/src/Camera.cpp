#include "Camera.h"

Camera::Camera(const glm::vec3& center)
	: m_center(center)
	, m_viewMatrix(1.0f)
	, m_lastCursorPos()
{
}

void Camera::OnEvent(core::event::Event& event)
{
	core::event::EventDispatcher dispatcher(event);

	dispatcher.Dispatch<core::event::MouseButtonPressedEvent>(
		[this](core::event::MouseButtonPressedEvent& e) {
			if (e.GetMouseButton() == GLFW_MOUSE_BUTTON_LEFT)
				m_dragging = true;
			return true;
		});

	dispatcher.Dispatch<core::event::MouseButtonReleasedEvent>(
		[this](core::event::MouseButtonReleasedEvent& e) {
			if (e.GetMouseButton() == GLFW_MOUSE_BUTTON_LEFT)
				m_dragging = false;
			return true;
		});

	dispatcher.Dispatch<core::event::MouseMovedEvent>(
		[this](core::event::MouseMovedEvent& e) {
			glm::vec2 pos(e.GetX(), e.GetY());
			if (m_dragging)
			{
				auto delta = pos - m_lastCursorPos;
				m_yawAngle += delta.x;
				m_pitchAngle += delta.y;
				m_pitchAngle = std::max(-89.0f, std::min(89.0f, m_pitchAngle));
				UpdateViewMatrix();
			}
			m_lastCursorPos = pos;
			return true;
		});
}

void Camera::OnDraw(gfx::Program& prog)
{
	prog.SetUniformMatrix4fv("m_view", m_viewMatrix);
}

void Camera::UpdateViewMatrix()
{
	glm::vec3 v = glm::vec3(0.0f, 0.0f, 0.0f) - m_center;
	float d = glm::length(v);
	glm::vec3 n = glm::normalize(v);
	float yaw = glm::radians(m_yawAngle), pitch = glm::radians(m_pitchAngle);
	n.x = glm::sin(yaw) * glm::cos(pitch);
	n.z = glm::cos(yaw) * glm::cos(pitch);
	n.y = glm::sin(pitch);

	glm::vec3 cameraPos = m_center + (n * d);

	m_viewMatrix = glm::lookAt(cameraPos, m_center, glm::vec3(0.0f, 0.0f, 1.0f));
}
