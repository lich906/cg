#pragma once

#include <unordered_map>
#include <optional>

#include "SpaceObjectView.h"

class UniverseViewModel
{
public:
	void AddNewObjectView(size_t uid, SpaceObjectViewPtr&& objectView);

	void RemoveAllObjectViews();

	void Draw(int width, int height);

	std::optional<size_t> FindObjectAtPos(const Vector& normalizedPos) const;

	void MoveObjectView(size_t uid, const Vector& deltaPos);

private:

	std::unordered_map<size_t, SpaceObjectViewPtr> m_objectViews;
};
