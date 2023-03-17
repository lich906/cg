#pragma once

#include <set>

#include "IObservableSpaceObject.h"

class ObservableSpaceObject : public IObservableSpaceObject
{
public:

// Inherited via IObservableSpaceObject
	void Subsribe(ISpaceObjectObserver* observerPtr) override;

protected:

	void Moved(const Vector& deltaPos);

private:
	std::set<ISpaceObjectObserver*> m_observers;
};
