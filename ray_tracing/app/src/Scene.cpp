#include "Scene.h"

int Scene::AddObject(std::unique_ptr<ISceneObject>&& object)
{
	int index = m_objects.size();
	m_objects.emplace_back(std::move(object));
	return index;
}

void Scene::IterateObjects(const std::function<void(const ISceneObject*, int)>& callbackFn) const
{
	for (size_t index = 0; index < m_objects.size(); index++)
	{
		callbackFn(m_objects[index].get(), static_cast<int>(index));
	}
}

const ISceneObject& Scene::GetObject(size_t index) const
{
	return *m_objects[index];
}
