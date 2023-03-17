#include "model/ObservableSpaceObject.h"

void ObservableSpaceObject::Subsribe(ISpaceObjectObserver* observerPtr)
{
	m_observers.insert(observerPtr);
}

void ObservableSpaceObject::Moved(const Vector& deltaPos)
{
	for (auto& obs : m_observers)
	{
		obs->OnSpaceObjectMove(deltaPos);
	}
}
