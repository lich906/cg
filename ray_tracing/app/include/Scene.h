#pragma once

#include <memory>
#include <functional>

#include "ISceneObject.h"
#include "PointLight.h"

class Scene
{
public:
	int AddPointLight(const PointLight& pointLight);
	int AddObject(std::unique_ptr<ISceneObject>&& object);
	void IterateObjects(const std::function<bool(const ISceneObject*, int)>& callbackFn) const;
	void IteratePointLights(const std::function<bool(const PointLight&)>& callbackFn) const;
	const ISceneObject& GetObject(size_t index) const;

private:
	std::vector<std::unique_ptr<ISceneObject>> m_objects;
	std::vector<PointLight> m_pointLights;
};
