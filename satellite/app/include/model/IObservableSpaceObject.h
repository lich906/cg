#pragma once

#include "ISpaceObjectObserver.h"

class IObservableSpaceObject
{
public:
	virtual ~IObservableSpaceObject() = default;

	virtual void Subsribe(ISpaceObjectObserver* observerPtr, bool instantNotify = false) = 0;
};
