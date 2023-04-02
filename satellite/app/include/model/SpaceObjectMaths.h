#pragma once

#include <vector>

#include "graphics/Vector.h"
#include "SpaceObject.h"
#include "Config.h"

class SpaceObjectMaths
{
public:
	static gfx::Vector GetObjectAcceleration(const std::vector<std::unique_ptr<SpaceObject>>& objects, size_t index);

	static float GetDistance(const SpaceObject& obj1, const SpaceObject& obj2);
};
