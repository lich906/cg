#include "model/GravityProcessor.h"

Vector GravityProcessor::FindBodyAcceleration(const std::vector<SpaceObject>& objects, size_t index)
{
	auto targetObjPos = objects[index].GetCurrentPosition();

	Vector accelerationVec;

	for (size_t i = 0; i < objects.size(); ++i)
	{
		if (i != index)
		{
			auto pos = objects[i].GetCurrentPosition();
			auto m = objects[i].GetMass();
			accelerationVec.x += m / powf(pos.x - targetObjPos.x, 2);
			accelerationVec.y += m / powf(pos.y - targetObjPos.y, 2);
		}
	}

	return { accelerationVec.x * config::GravitationCoeff, accelerationVec.y * config::GravitationCoeff };
}

void GravityProcessor::ResetCachedDistances()
{
	m_distances.clear();
}
