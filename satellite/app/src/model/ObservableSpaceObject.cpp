#include "model/ObservableSpaceObject.h"

void ObservableSpaceObject::Subsribe(ISpaceObjectObserver* observerPtr)
{
	m_observers.insert(observerPtr);
}

void ObservableSpaceObject::Moved(const gfx::Vector& pos)
{
	for (auto& obs : m_observers)
	{
		obs->OnSpaceObjectMove(pos);
	}
}

void ObservableSpaceObject::VelocityChanged(const gfx::Vector& value)
{
	for (auto& obs : m_observers)
	{
		obs->OnVelocityChange(value);
	}
}
