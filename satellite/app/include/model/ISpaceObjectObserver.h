#pragma once

#include "graphics/Vector.h"

struct ISpaceObjectObserver
{
	virtual ~ISpaceObjectObserver() = default;

	virtual void OnSpaceObjectMove(const gfx::Vector& pos) = 0;
	virtual void OnVelocityChange(const gfx::Vector& value) = 0;
};
