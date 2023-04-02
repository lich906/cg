#pragma once

#include <functional>
#include <stdexcept>

#include "SpaceObject.h"
#include "SpaceObjectMaths.h"

class UniverseModel
{
public:
	using FindIfCallback = std::function<bool(const std::unique_ptr<SpaceObject>& object)>;
	using ForEachCallback = std::function<void(const std::unique_ptr<SpaceObject>& object)>;

	void AddNewObject(std::unique_ptr<SpaceObject>&& obj);

	void RemoveAllObjects();

	SpaceObject* FindIf(const FindIfCallback& callback);

	/*
		Returns 'true' if objects are present, 'false' otherwise.
	*/
	bool NextState(float dt);

	void ForEach(const ForEachCallback& callback);

	Connection RegisterCollisionObs(const VectorSignal::slot_type& slot);

private:

	void ProcessCollisions();

	gfx::Vector GetDistance(const SpaceObject& obj1, const SpaceObject& obj2);

	std::vector<std::unique_ptr<SpaceObject>> m_objects;

	VectorSignal m_collisionSignal;
};
