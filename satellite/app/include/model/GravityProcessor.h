#pragma once

#include <vector>
#include <unordered_map>

#include "types/Vector.h"
#include "SpaceObject.h"
#include "Config.h"

class GravityProcessor
{
public:
	Vector FindObjectAcceleration(const std::unordered_map<size_t, SpaceObjectPtr>& objects, size_t uid);
};
