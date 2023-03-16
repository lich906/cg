#pragma once

#include "SpaceObject.h"
#include "GravityProcessor.h"

class UniverseModel
{
public:

	void AddNewObject(SpaceObject&& obj);

	void RemoveAllObjects();

	void ChangeObjectPosition(size_t id, const Vector& pos);

	void ChangeObjectVelocity(size_t id, const Vector& vel);

	void NextState(float dt);

private:

	std::unordered_map<size_t, SpaceObject> m_spaceObjects;

	GravityProcessor m_gravityProcessor;
};
