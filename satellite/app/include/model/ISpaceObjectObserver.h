#pragma once

#include "types/Vector.h"

struct ISpaceObjectObserver
{
	virtual ~ISpaceObjectObserver() = default;

	virtual void OnSpaceObjectMove(const Vector& deltaPos) = 0;
};
