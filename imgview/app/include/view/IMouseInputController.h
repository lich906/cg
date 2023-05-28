#pragma once

#include <glm/glm.hpp>

struct IMouseInputController
{
	virtual ~IMouseInputController() = default;

	virtual void OnMouseDown(const glm::vec2& cursorPos) = 0;
	virtual void OnMouseUp(const glm::vec2& cursorPos) = 0;
	virtual void OnMouseMove(const glm::vec2& cursorPos, const glm::vec2& delta) = 0;
	virtual void OnScrollUp(const glm::vec2& cursorPos) = 0;
	virtual void OnScrollDown(const glm::vec2& cursorPos) = 0;
};
