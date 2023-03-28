#include "model/GravityProcessor.h"

gfx::Vector GravityProcessor::FindObjectAcceleration(const std::vector<std::unique_ptr<SpaceObject>>& objects, size_t index)
{
	auto targetObjPos = objects.at(index)->GetCurrentPosition();

	gfx::Vector aVec;

	for (size_t i = 0; i < objects.size(); i++)
	{
		if (i != index)
		{
			auto objPos = objects[i]->GetCurrentPosition();
			auto m = objects[i]->GetMass();
			gfx::Vector r(objPos.x - targetObjPos.x, objPos.y - targetObjPos.y);
			float aMod = m / r.SquareMod();
			aVec += r.Unit() * aMod;
		}
	}

	return aVec * config::GravitationCoeff;
}
