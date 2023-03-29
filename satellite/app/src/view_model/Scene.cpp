#include "view_model/Scene.h"

void Scene::AddNewObject(std::unique_ptr<SceneObject>&& object)
{
	object->SetDeleter(CreateDeleter(object.get()));
	m_objects.emplace_back(std::move(object));
}

void Scene::RemoveAllObjects()
{
	m_objects.clear();
}

void Scene::Draw(int width, int height)
{
	for (auto&& object : m_objects)
	{
		object->Draw(width, height);
	}
}

SceneObject::ObjectDeleter Scene::CreateDeleter(const SceneObject* ptr)
{
	return [this](const SceneObject* ptr) {
		std::erase_if(m_objects, [ptr](const std::unique_ptr<SceneObject>& obj) {
			return obj.get() == ptr;
		});
	};
}
