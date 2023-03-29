#pragma once

#include <set>

#include "IObservableSpaceObject.h"

class ObservableSpaceObject : public IObservableSpaceObject
{
public:
	// Inherited via IObservableSpaceObject
	virtual void Subsribe(ISpaceObjectObserver* observerPtr, bool instantNotify) override;

protected:

	void Moved();
	void VelocityChanged();

private:

	virtual gfx::Vector GetPosition() const = 0;
	virtual gfx::Vector GetVelocity() const = 0;

	std::set<ISpaceObjectObserver*> m_observers;
};
