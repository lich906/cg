#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "core/Input.h"

Camera::Camera(const glm::vec3& position, const glm::vec3& fwdDirection)
	: m_Position(position)
	, m_ForwardDirection(fwdDirection)
{
}

bool Camera::OnUpdate(float ts)
{
	auto [mx, my] = core::Input::GetMousePosition();
	glm::vec2 mousePos(mx, my);
	glm::vec2 delta = (mousePos - m_LastMousePosition) * 0.002f;
	m_LastMousePosition = mousePos;

	if (!core::Input::IsMouseButtonDown(core::MouseButton::Right))
	{
		core::Input::SetCursorMode(core::CursorMode::Normal);
		return false;
	}

	core::Input::SetCursorMode(core::CursorMode::Locked);

	bool moved = false;

	constexpr glm::vec3 upDirection(0.0f, 1.0f, 0.0f);
	glm::vec3 rightDirection = glm::cross(m_ForwardDirection, upDirection);

	float speed = 5.0f;

	// Movement
	if (core::Input::IsKeyDown(core::KeyCode::W))
	{
		m_Position += m_ForwardDirection * speed * ts;
		moved = true;
	}
	else if (core::Input::IsKeyDown(core::KeyCode::S))
	{
		m_Position -= m_ForwardDirection * speed * ts;
		moved = true;
	}
	if (core::Input::IsKeyDown(core::KeyCode::A))
	{
		m_Position -= rightDirection * speed * ts;
		moved = true;
	}
	else if (core::Input::IsKeyDown(core::KeyCode::D))
	{
		m_Position += rightDirection * speed * ts;
		moved = true;
	}
	if (core::Input::IsKeyDown(core::KeyCode::Q))
	{
		m_Position -= upDirection * speed * ts;
		moved = true;
	}
	else if (core::Input::IsKeyDown(core::KeyCode::E))
	{
		m_Position += upDirection * speed * ts;
		moved = true;
	}

	// Rotation
	if (delta.x != 0.0f || delta.y != 0.0f)
	{
		float pitchDelta = delta.y * GetRotationSpeed();
		float yawDelta = delta.x * GetRotationSpeed();

		glm::quat q = glm::normalize(glm::cross(glm::angleAxis(-pitchDelta, rightDirection),
			glm::angleAxis(-yawDelta, glm::vec3(0.f, 1.0f, 0.0f))));
		m_ForwardDirection = glm::rotate(q, m_ForwardDirection);

		moved = true;
	}

	if (moved)
	{
		RecalculateView();
		RecalculateRayDirections();
	}

	return moved;
}

void Camera::OnResize(uint32_t width, uint32_t height)
{
	if (width == m_ViewportWidth && height == m_ViewportHeight)
		return;

	m_ViewportWidth = width;
	m_ViewportHeight = height;

	RecalculateProjection();
	RecalculateRayDirections();
}

float Camera::GetRotationSpeed()
{
	return 0.3f;
}

void Camera::RecalculateProjection()
{
	m_Projection = glm::perspectiveFov(glm::radians(m_VerticalFOV), (float)m_ViewportWidth, (float)m_ViewportHeight, m_NearClip, m_FarClip);
	m_InverseProjection = glm::inverse(m_Projection);
}

void Camera::RecalculateView()
{
	m_View = glm::lookAt(m_Position, m_Position + m_ForwardDirection, glm::vec3(0, 1, 0));
	m_InverseView = glm::inverse(m_View);
}

void Camera::RecalculateRayDirections()
{
	m_RayDirections.resize(m_ViewportWidth * m_ViewportHeight);

	for (uint32_t y = 0; y < m_ViewportHeight; y++)
	{
		for (uint32_t x = 0; x < m_ViewportWidth; x++)
		{
			glm::vec2 coord = { (float)x / (float)m_ViewportWidth, (float)y / (float)m_ViewportHeight };
			coord = coord * 2.0f - 1.0f; // -1 -> 1

			glm::vec4 target = m_InverseProjection * glm::vec4(coord.x, coord.y, 1, 1);
			glm::vec3 rayDirection = glm::vec3(m_InverseView * glm::vec4(glm::normalize(glm::vec3(target) / target.w), 0)); // World space
			m_RayDirections[x + y * m_ViewportWidth] = rayDirection;
		}
	}
}
