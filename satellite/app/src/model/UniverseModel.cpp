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

bool UniverseModel::NextState(float dt)
{
	ProcessCollisions();

	for (size_t i = 0; i < m_objects.size(); ++i)
	{
		auto acceleration = SpaceObjectMaths::GetObjectAcceleration(m_objects, i);
		m_objects[i]->NextPosition(acceleration, dt);
	}

	return !m_objects.empty();
}

void UniverseModel::ForEach(const ForEachCallback& callback)
{
	for (auto& object : m_objects)
	{
		callback(object);
	}
}

Connection UniverseModel::RegisterCollisionObs(const VectorSignal::slot_type& slot)
{
	return m_collisionSignal.connect(slot);
}

void UniverseModel::ProcessCollisions()
{
	for (size_t i = 0; i < m_objects.size(); ++i)
	{
		for (size_t j = i + 1; j < m_objects.size(); ++j)
		{
			float distance = SpaceObjectMaths::GetDistance(*m_objects[i], *m_objects[j]);
			if (distance == 0.0f)
			{
				m_collisionSignal(m_objects[i]->GetCurrentPosition());
				m_collisionSignal(m_objects[j]->GetCurrentPosition());

				m_objects.erase(m_objects.begin() + i);
				m_objects.erase(m_objects.begin() + j - 1);
			}
		}
	}
}

gfx::Vector UniverseModel::GetDistance(const SpaceObject& obj1, const SpaceObject& obj2)
{
	return gfx::Vector();
}
