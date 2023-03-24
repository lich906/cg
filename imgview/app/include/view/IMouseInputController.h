#pragma once

#include "graphics/Vector.h"

struct IMouseInputController
{
	virtual ~IMouseInputController() = default;

	virtual void OnMouseDown(const Vector& pos) = 0;
	virtual void OnMouseUp(const Vector& pos) = 0;
	virtual void OnMouseMove(const Vector& delta) = 0;
	virtual void OnScrollUp(float offset) = 0;
	virtual void OnScrollDown(float offset) = 0;
};
