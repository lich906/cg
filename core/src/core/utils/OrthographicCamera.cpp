#include "corepch.h"

#include "core/utils/OrthographicCamera.h"

core::utils::OrthographicCamera::OrthographicCamera(int controlMouseBtn)
	: m_controlMouseButton(controlMouseBtn)
{
}

void core::utils::OrthographicCamera::OnEvent(event::Event& event)
{
	event::EventDispatcher dispatcher(event);

	dispatcher.Dispatch<event::MouseButtonPressedEvent>(
		[this](const event::MouseButtonPressedEvent& e) {
			if (e.GetMouseButton() == m_controlMouseButton)
				m_controlMouseButtonPressed = true;
			return false;
		});

	dispatcher.Dispatch<event::MouseButtonReleasedEvent>(
		[this](const event::MouseButtonReleasedEvent& e) {
			if (e.GetMouseButton() == m_controlMouseButton)
				m_controlMouseButtonPressed = false;
			return false;
		});

	dispatcher.Dispatch<event::MouseMovedEvent>(
		std::bind(&OrthographicCamera::OnMouseMoved, this, std::placeholders::_1));
}

boost::signals2::connection core::utils::OrthographicCamera::SubscribeOnViewMatrixChange(const MatrixSignal::slot_type& slot)
{
	return m_viewMatrixSignal.connect(slot);
}

void core::utils::OrthographicCamera::TransformScreenCoords(float& x, float& y) const
{
	x -= m_position.x;
	y -= m_position.y;
}

bool core::utils::OrthographicCamera::OnMouseMoved(const event::MouseMovedEvent& e)
{
	glm::vec2 cursorPos(e.GetX(), e.GetY());

	if (m_controlMouseButtonPressed)
	{
		m_position += cursorPos - m_lastCursorPos;
		m_viewMatrixSignal(glm::translate(glm::mat4(1.0f), glm::vec3(m_position, 0.0f)));
	}

	m_lastCursorPos = cursorPos;

	return false;
}
