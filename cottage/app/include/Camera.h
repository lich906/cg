#pragma once

#include "consts.h"
#include "Object.h"

class Camera : public Object
{
public:
	Camera(const glm::vec3& center);

	virtual void OnEvent(core::event::Event& e) override;
	virtual void OnDraw(gfx::Program& prog) override;

private:
	bool OnMouseBtnPressed(core::event::MouseButtonPressedEvent& event);
	bool OnMouseBtnReleased(core::event::MouseButtonReleasedEvent& event);
	bool OnMouseMoved(core::event::MouseMovedEvent& event);
	bool OnMouseScrolled(core::event::MouseScrolledEvent& event);
	void UpdateViewMatrix();

	glm::mat4 m_viewMatrix;
	glm::vec3 m_center;
	glm::vec3 m_cameraPos;
	glm::vec2 m_lastCursorPos;

	float m_pitchAngle = 0.0f, m_yawAngle = 0.0f, m_zoomLevel = 0.0f;
	bool m_dragging = false;
	bool m_matrixChanged = true;
};
