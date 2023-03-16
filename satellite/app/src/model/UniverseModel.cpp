#include "model/UniverseModel.h"

void UniverseModel::AddNewObject(SpaceObject&& obj)
{
	m_spaceObjects.insert({ obj.GetId(), std::move(obj) });
}

void UniverseModel::RemoveAllObjects()
{
	m_spaceObjects.clear();
}

void UniverseModel::ChangeObjectPosition(size_t id, const Vector& pos)
{
	auto obj = m_spaceObjects.find(id);

	if (obj != m_spaceObjects.end())
	{
		obj->second.SetCurrentPosition(pos);
	}
}

void UniverseModel::ChangeObjectVelocity(size_t id, const Vector& vel)
{
	auto obj = m_spaceObjects.find(id);

	if (obj != m_spaceObjects.end())
	{
		obj->second.SetCurrentVelocity(vel);
	}
}

void UniverseModel::NextState(float dt)
{
	for (auto& [id, object] : m_spaceObjects)
	{
		object.NextPosition(dt);
	}
}
