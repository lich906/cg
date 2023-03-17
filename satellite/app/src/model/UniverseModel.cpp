#include "model/UniverseModel.h"

void UniverseModel::AddNewObject(SpaceObjectPtr&& obj)
{
	m_spaceObjects.insert({ obj->GetId(), std::move(obj) });
}

void UniverseModel::RemoveAllObjects()
{
	m_spaceObjects.clear();
}

void UniverseModel::MoveObject(size_t id, const Vector& deltaPos)
{
	auto obj = m_spaceObjects.find(id);

	if (obj != m_spaceObjects.end())
	{
		auto pos = obj->second->GetCurrentPosition();
		obj->second->SetCurrentPosition(pos += deltaPos);
	}
}

void UniverseModel::ChangeObjectVelocity(size_t id, const Vector& vel)
{
	auto obj = m_spaceObjects.find(id);

	if (obj != m_spaceObjects.end())
	{
		obj->second->SetCurrentVelocity(vel);
	}
}

void UniverseModel::NextState(float dt)
{
	for (auto& [id, object] : m_spaceObjects)
	{
		object->NextPosition(dt);
	}
}
