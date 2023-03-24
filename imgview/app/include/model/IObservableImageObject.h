#pragma once

#include "IImageObjectObserver.h"

struct IObservableImageObject
{
	virtual ~IObservableImageObject() = default;

	virtual void SubscribeOnTransform(IImageObjectObserver* observerPtr, bool instantNotify = false) = 0;
};
