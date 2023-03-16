#pragma once

#include <vector>
#include <unordered_map>

#include "types/Vector.h"
#include "SpaceObject.h"
#include "Config.h"

class GravityProcessor
{
public:

	Vector FindBodyAcceleration(const std::vector<SpaceObject>& objects, size_t index);

	void ResetCachedDistances();

private:

	std::unordered_map<size_t, std::unordered_map<size_t, float>> m_distances;
};
