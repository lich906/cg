#include "Camera.h"
#include "glm/gtx/rotate_vector.hpp"

#define BIND_CAMERA_EVENT_FN(x) std::bind(&Camera::x, this, std::placeholders::_1)

static constexpr float CONTROL_SPEED = 0.3f;

Camera::Camera(const glm::vec3& center)
	: m_center(center)
	, m_viewMatrix(1.0f)
	, m_lastCursorPos()
	, m_cameraPos()
{
}

void Camera::OnEvent(core::event::Event& event)
{
	core::event::EventDispatcher dispatcher(event);

	dispatcher.Dispatch<core::event::MouseButtonPressedEvent>(BIND_CAMERA_EVENT_FN(OnMouseBtnPressed));
	dispatcher.Dispatch<core::event::MouseButtonReleasedEvent>(BIND_CAMERA_EVENT_FN(OnMouseBtnReleased));
	dispatcher.Dispatch<core::event::MouseMovedEvent>(BIND_CAMERA_EVENT_FN(OnMouseMoved));
	dispatcher.Dispatch<core::event::MouseScrolledEvent>(BIND_CAMERA_EVENT_FN(OnMouseScrolled));
}

void Camera::OnDraw(gfx::Program& prog)
{
	prog.SetUniform3fv("u_viewPos", m_cameraPos);
	prog.SetUniformMatrix4fv("m_view", m_viewMatrix);
}

bool Camera::OnMouseBtnPressed(core::event::MouseButtonPressedEvent& event)
{
	if (event.GetMouseButton() == GLFW_MOUSE_BUTTON_LEFT)
	{
		m_dragging = true;
	}
	return true;
}

bool Camera::OnMouseBtnReleased(core::event::MouseButtonReleasedEvent& event)
{
	if (event.GetMouseButton() == GLFW_MOUSE_BUTTON_LEFT)
	{
		m_dragging = false;
	}
	return true;
}

bool Camera::OnMouseMoved(core::event::MouseMovedEvent& event)
{
	glm::vec2 pos(event.GetX(), event.GetY());
	if (m_dragging)
	{
		auto delta = pos - m_lastCursorPos;
		m_yawAngle -= delta.x * CONTROL_SPEED;
		m_pitchAngle += delta.y * CONTROL_SPEED;
		m_pitchAngle = std::max(-89.0f, std::min(89.0f, m_pitchAngle));
		UpdateViewMatrix();
	}
	m_lastCursorPos = pos;
	return true;
}

bool Camera::OnMouseScrolled(core::event::MouseScrolledEvent& event)
{
	m_zoomLevel -= event.GetYOffset() * CONTROL_SPEED;
	UpdateViewMatrix();
	return true;
}

void Camera::UpdateViewMatrix()
{
	float distance = glm::length(m_center);
	glm::vec3 v = glm::normalize(-m_center); // orth from center to origin
	v = glm::normalize(glm::rotate(v, glm::radians(m_yawAngle), glm::vec3(0.0f, 1.0f, 0.0f))); // rotate in ZX surface
	glm::vec3 perp = glm::vec3(v.z, v.y, -v.x); // perpendicular to vector 'v' laying in ZX surface
	v = glm::normalize(glm::rotate(v, glm::radians(m_pitchAngle), perp));

	m_cameraPos = m_center + (v * (distance + m_zoomLevel));
	m_viewMatrix = glm::lookAt(m_cameraPos, m_center, glm::vec3(0.0f, 1.0f, 0.0f));
}
