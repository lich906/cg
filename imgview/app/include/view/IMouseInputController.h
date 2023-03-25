#pragma once

#include "graphics/Vector.h"

struct IMouseInputController
{
	virtual ~IMouseInputController() = default;

	virtual void OnMouseDown(const Vector& cursorPos) = 0;
	virtual void OnMouseUp(const Vector& cursorPos) = 0;
	virtual void OnMouseMove(const Vector& cursorPos, const Vector& delta) = 0;
	virtual void OnScrollUp(const Vector& cursorPos) = 0;
	virtual void OnScrollDown(const Vector& cursorPos) = 0;
};
