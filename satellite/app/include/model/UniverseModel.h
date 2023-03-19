#pragma once

#include <functional>
#include <stdexcept>

#include "SpaceObject.h"
#include "GravityProcessor.h"

class UniverseModel
{
public:

	using ForEachCallback = std::function<void(SpaceObjectPtr& object)>;

	void AddNewObject(SpaceObjectPtr&& obj);

	void RemoveAllObjects();

	/*
		@throw std::out_of_range : Object not found.
	*/
	SpaceObjectPtr& GetObject(size_t uid);

	void NextState(float dt);

	void ForEach(const ForEachCallback& callback);

private:

	std::unordered_map<size_t, SpaceObjectPtr> m_spaceObjects;

	GravityProcessor m_gravityProcessor;
};
