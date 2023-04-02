#include "model/SpaceObjectMaths.h"

gfx::Vector SpaceObjectMaths::GetObjectAcceleration(const std::vector<std::unique_ptr<SpaceObject>>& objects, size_t index)
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

float SpaceObjectMaths::GetDistance(const SpaceObject& obj1, const SpaceObject& obj2)
{
	gfx::Vector d = obj1.GetCurrentPosition() - obj2.GetCurrentPosition();
	return std::max(d.Mod() - std::min(obj1.GetRadius(), obj2.GetRadius()), 0.0f);
}
