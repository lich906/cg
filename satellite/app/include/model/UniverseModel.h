#pragma once

#include <functional>
#include <stdexcept>

#include "SpaceObject.h"
#include "GravityProcessor.h"

class UniverseModel
{
public:
	using FindIfCallback = std::function<bool(std::unique_ptr<SpaceObject>& object)>;
	using ForEachCallback = std::function<void(std::unique_ptr<SpaceObject>& object)>;

	void AddNewObject(std::unique_ptr<SpaceObject>&& obj);

	void RemoveAllObjects();

	SpaceObject* FindIf(const FindIfCallback& callback);

	void NextState(float dt);

	void ForEach(const ForEachCallback& callback);

private:

	std::vector<std::unique_ptr<SpaceObject>> m_objects;

	GravityProcessor m_gravityProcessor;
};
