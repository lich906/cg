#pragma once

#include <vector>

#include "view_model/SceneObject.h"

class Scene
{
public:
	Scene();

	void AddNewObject(std::unique_ptr<SceneObject>&& object);

	void RemoveAllObjects();

	void Draw(int width, int height);

private:

	SceneObject::ObjectDeleter CreateDeleter(const SceneObject* ptr);

	std::vector<std::unique_ptr<SceneObject>> m_objects;
	std::unique_ptr<SceneObject> m_background;
};
