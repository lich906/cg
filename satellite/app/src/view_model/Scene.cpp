#include "view_model/Scene.h"
#include "view_model/Background.h"

Scene::Scene()
	: m_background(std::make_unique<Background>())
{
}

void Scene::AddNewObject(std::unique_ptr<SceneObject>&& object)
{
	object->SetRemoveCallback(CreateDeleter(object.get()));
	m_objects.emplace_back(std::move(object));
}

void Scene::Draw(int width, int height)
{
	m_background->Draw(width, height);

	for (auto&& object : m_objects)
	{
		object->Draw(width, height);
	}
}

SceneObject::RemoveCallback Scene::CreateDeleter(const SceneObject* ptr)
{
	return [this](const SceneObject* ptr) {
		std::erase_if(m_objects, [ptr](const std::unique_ptr<SceneObject>& obj) {
			return obj.get() == ptr;
		});
	};
}
