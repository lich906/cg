#pragma once

#include <vector>

#include "graphics/Vector.h"
#include "SpaceObject.h"
#include "Config.h"

class GravityProcessor
{
public:
	gfx::Vector FindObjectAcceleration(const std::vector<std::unique_ptr<SpaceObject>>& objects, size_t index);
};
