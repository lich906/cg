#include "model/GravityProcessor.h"

Vector GravityProcessor::FindObjectAcceleration(const std::unordered_map<size_t, SpaceObjectPtr>& objects, size_t uid)
{
	auto targetObjPos = objects.at(uid)->GetCurrentPosition();

	Vector aVec;

	for (auto& [id, object] : objects)
	{
		if (id != uid)
		{
			auto objPos = object->GetCurrentPosition();
			auto m = object->GetMass();
			Vector r(objPos.x - targetObjPos.x, objPos.y - targetObjPos.y);
			float aMod = m / r.SquareMod();
			aVec += r.Unit() * aMod;
		}
	}

	return aVec * config::GravitationCoeff;
}
