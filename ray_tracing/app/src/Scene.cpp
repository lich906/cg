#include "Scene.h"

int Scene::AddPointLight(const PointLight& pointLight)
{
	size_t index = m_pointLights.size();
	m_pointLights.push_back(pointLight);
	return (int)index;
}

int Scene::AddObject(std::unique_ptr<ISceneObject>&& object)
{
	size_t index = m_objects.size();
	m_objects.emplace_back(std::move(object));
	return (int)index;
}

void Scene::IterateObjects(const std::function<bool(const ISceneObject*, int)>& callbackFn) const
{
	for (size_t index = 0; index < m_objects.size(); index++)
	{
		if (!callbackFn(m_objects[index].get(), static_cast<int>(index)))
			break;
	}
}

void Scene::IteratePointLights(const std::function<bool(const PointLight&)>& callbackFn) const
{
	for (auto&& pointLight : m_pointLights)
	{
		if (!callbackFn(pointLight))
			break;
	}
}

const ISceneObject& Scene::GetObject(size_t index) const
{
	return *m_objects[index];
}

ISceneObject& Scene::GetObject(size_t index)
{
	return *m_objects[index];
}

void Scene::RemoveObject(size_t index)
{
	m_objects.erase(m_objects.begin() + index);
}
