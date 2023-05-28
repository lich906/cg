#include "model/SpaceObjectMaths.h"

glm::vec2 SpaceObjectMaths::GetObjectAcceleration(const std::vector<std::unique_ptr<SpaceObject>>& objects, size_t index)
{
	auto targetObjPos = objects.at(index)->GetCurrentPosition();

	glm::vec2 aVec{};

	for (size_t i = 0; i < objects.size(); i++)
	{
		if (i != index)
		{
			auto objPos = objects[i]->GetCurrentPosition();
			auto m = objects[i]->GetMass();
			glm::vec2 r(objPos.x - targetObjPos.x, objPos.y - targetObjPos.y);
			float aMod = m / std::powf(glm::length(r), 2.0f);
			aVec += (glm::normalize(r) * aMod);
		}
	}

	return aVec * config::GravitationCoeff;
}

float SpaceObjectMaths::GetDistance(const SpaceObject& obj1, const SpaceObject& obj2)
{
	glm::vec2 d = obj1.GetCurrentPosition() - obj2.GetCurrentPosition();
	return std::max(glm::length(d) - std::min(obj1.GetRadius(), obj2.GetRadius()), 0.0f);
}
