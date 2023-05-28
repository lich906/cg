#include "view/Camera.h"

void Camera::OnCameraMove(const glm::vec2& delta)
{
	m_offset += delta;
}

glm::vec2 Camera::GetOffset()
{
	return m_offset;
}

void Camera::UpdateViewMatrix()
{
	gfx::CurrentProgram::Get().SetUniformMatrix4fv("m_view",
		glm::translate(glm::mat4(1.0f), glm::vec3(m_offset.x, m_offset.y, 0.0f)));
}

void Camera::Reset()
{
	m_offset.x = 0.0f;
	m_offset.y = 0.0f;
}
