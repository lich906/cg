#include "model/UniverseModel.h"

void UniverseModel::AddNewObject(std::unique_ptr<SpaceObject>&& obj)
{
	m_objects.emplace_back(std::move(obj));
}

void UniverseModel::RemoveAllObjects()
{
	m_objects.clear();
}

SpaceObject* UniverseModel::FindIf(const FindIfCallback& callback)
{
	auto iterator = std::find_if(m_objects.begin(), m_objects.end(), callback);

	if (iterator != m_objects.end())
	{
		return iterator->get();
	}

	return nullptr;
}

void UniverseModel::NextState(float dt)
{
	for (size_t i = 0; i < m_objects.size(); ++i)
	{
		auto acceleration = m_gravityProcessor.FindObjectAcceleration(m_objects, i);
		m_objects[i]->NextPosition(acceleration, dt);
	}
}

void UniverseModel::ForEach(const ForEachCallback& callback)
{
	for (auto& object : m_objects)
	{
		callback(object);
	}
}
