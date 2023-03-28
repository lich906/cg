#pragma once

#include "ISpaceObjectObserver.h"

struct IObservableSpaceObject
{
	virtual ~IObservableSpaceObject() = default;

	virtual void Subsribe(ISpaceObjectObserver* observerPtr) = 0;
};
