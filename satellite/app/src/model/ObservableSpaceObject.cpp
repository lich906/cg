#include "model/ObservableSpaceObject.h"

void ObservableSpaceObject::Subsribe(ISpaceObjectObserver* observerPtr, bool instantNotify)
{
	m_observers.insert(observerPtr);

	if (instantNotify)
	{
		observerPtr->OnSpaceObjectMove(GetPosition());
		observerPtr->OnVelocityChange(GetVelocity());
	}
}

void ObservableSpaceObject::Moved()
{
	auto pos = GetPosition();
	for (auto& obs : m_observers)
	{
		obs->OnSpaceObjectMove(pos);
	}
}

void ObservableSpaceObject::VelocityChanged()
{
	auto vel = GetVelocity();
	for (auto& obs : m_observers)
	{
		obs->OnVelocityChange(vel);
	}
}
