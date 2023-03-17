#pragma once

#include "SpaceObject.h"
#include "GravityProcessor.h"

class UniverseModel
{
public:

	void AddNewObject(SpaceObjectPtr&& obj);

	void RemoveAllObjects();

	void MoveObject(size_t id, const Vector& deltaPos);

	void ChangeObjectVelocity(size_t id, const Vector& vel);

	void NextState(float dt);

private:

	std::unordered_map<size_t, SpaceObjectPtr> m_spaceObjects;

	GravityProcessor m_gravityProcessor;
};
