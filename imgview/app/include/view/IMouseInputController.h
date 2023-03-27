#pragma once

#include "graphics/Vector.h"

struct IMouseInputController
{
	virtual ~IMouseInputController() = default;

	virtual void OnMouseDown(const gfx::Vector& cursorPos) = 0;
	virtual void OnMouseUp(const gfx::Vector& cursorPos) = 0;
	virtual void OnMouseMove(const gfx::Vector& cursorPos, const gfx::Vector& delta) = 0;
	virtual void OnScrollUp(const gfx::Vector& cursorPos) = 0;
	virtual void OnScrollDown(const gfx::Vector& cursorPos) = 0;
};
