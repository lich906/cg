#pragma once

#include <set>

#include "IObservableSpaceObject.h"

class ObservableSpaceObject : public IObservableSpaceObject
{
public:

// Inherited via IObservableSpaceObject
	void Subsribe(ISpaceObjectObserver* observerPtr) override;

protected:

	void Moved(const gfx::Vector& pos);
	void VelocityChanged(const gfx::Vector& value);

private:
	std::set<ISpaceObjectObserver*> m_observers;
};
