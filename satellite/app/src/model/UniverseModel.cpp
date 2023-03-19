#include "model/UniverseModel.h"

void UniverseModel::AddNewObject(SpaceObjectPtr&& obj)
{
	m_spaceObjects.insert({ obj->GetId(), std::move(obj) });
}

void UniverseModel::RemoveAllObjects()
{
	m_spaceObjects.clear();
}

SpaceObjectPtr& UniverseModel::GetObject(size_t uid)
{
	auto obj = m_spaceObjects.find(uid);

	if (obj != m_spaceObjects.end())
	{
		return obj->second;
	}

	throw std::out_of_range("Object with such id not found.");
}

void UniverseModel::NextState(float dt)
{
	for (auto& [id, object] : m_spaceObjects)
	{
		auto acceleration = m_gravityProcessor.FindObjectAcceleration(m_spaceObjects, id);
		auto velocityDelta = acceleration * dt;
		object->SetCurrentVelocity(object->GetCurrentVelocity() + velocityDelta);
	}

	for (auto& [id, object] : m_spaceObjects)
	{
		object->NextPosition(dt);
	}
}

void UniverseModel::ForEach(const ForEachCallback& callback)
{
	for (auto& [id, object] : m_spaceObjects)
	{
		callback(object);
	}
}
