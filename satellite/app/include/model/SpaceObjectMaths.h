#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "SpaceObject.h"
#include "Config.h"

class SpaceObjectMaths
{
public:
	static glm::vec2 GetObjectAcceleration(const std::vector<std::unique_ptr<SpaceObject>>& objects, size_t index);

	static float GetDistance(const SpaceObject& obj1, const SpaceObject& obj2);
};
