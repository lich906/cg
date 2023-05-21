#pragma once

#include <memory>
#include <functional>

#include "ISceneObject.h"

class Scene
{
public:
	int AddObject(std::unique_ptr<ISceneObject>&& object);
	void IterateObjects(const std::function<void(const ISceneObject*, int)>& callbackFn) const;
	const ISceneObject& GetObject(size_t index) const;

private:
	std::vector<std::unique_ptr<ISceneObject>> m_objects;
};
