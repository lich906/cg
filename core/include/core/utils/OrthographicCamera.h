#pragma once

#include "corepch.h"

#include "core/event/event_inc.h"

namespace core::utils
{

using MatrixSignal = boost::signals2::signal<void(const glm::mat4&)>;
using FloatSignal = boost::signals2::signal<void(float)>;

class OrthographicCamera
{
public:
	OrthographicCamera(int controlMouseBtn);

	void OnEvent(event::Event& e);
	boost::signals2::connection SubscribeOnViewMatrixChange(const MatrixSignal::slot_type& slot);
	inline glm::vec2 GetPosition() const { return m_position; };
	void TransformScreenCoords(float& x, float& y) const;

private:
	bool OnMouseMoved(const event::MouseMovedEvent& e);
	bool OnMouseScrolled(const event::MouseScrolledEvent& e);
	glm::mat4 GetViewMatrix();

	const int m_controlMouseButton;

	glm::vec2 m_lastCursorPos = glm::vec2();
	glm::vec2 m_position = glm::vec2();
	MatrixSignal m_viewMatrixSignal;
	bool m_controlMouseButtonPressed = false;
	float m_zoomLevel = 1.0f;
};

} // namespace core::utils
