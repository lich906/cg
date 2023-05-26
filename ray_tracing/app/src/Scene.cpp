#include "Scene.h"

int Scene::AddPointLight(const PointLight& spotLight)
{
	size_t index = m_pointLights.size();
	m_pointLights.push_back(spotLight);
	return (int)index;
}

int Scene::AddObject(std::unique_ptr<ISceneObject>&& object)
{
	size_t index = m_objects.size();
	m_objects.emplace_back(std::move(object));
	return (int)index;
}

void Scene::IterateObjects(const std::function<void(const ISceneObject*, int)>& callbackFn) const
{
	for (size_t index = 0; index < m_objects.size(); index++)
	{
		callbackFn(m_objects[index].get(), static_cast<int>(index));
	}
}

void Scene::IteratePointLights(const std::function<void(const PointLight&)>& callbackFn) const
{
	for (auto&& pointLight : m_pointLights)
	{
		callbackFn(pointLight);
	}
}

const ISceneObject& Scene::GetObject(size_t index) const
{
	return *m_objects[index];
}
