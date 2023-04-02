#pragma once

#include <vector>

#include "view_model/SceneObject.h"

class Scene
{
public:
	Scene();

	void AddNewObject(std::unique_ptr<SceneObject>&& object);

	void Draw(int width, int height);

	void Update(float alpha);

private:

	SceneObject::RemoveCallback CreateRemoveCallback(const SceneObject* ptr);

	std::vector<std::unique_ptr<SceneObject>> m_objects;
	std::unique_ptr<SceneObject> m_background;
};
