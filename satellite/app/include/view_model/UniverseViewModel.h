#pragma once

#include <unordered_map>
#include <optional>

#include "SpaceObjectView.h"

class UniverseViewModel
{
public:
	void AddNewObjectView(size_t uid, SpaceObjectView&& objectView);

	void RemoveAllObjectViews();

	void Draw(int width, int height);

	std::optional<size_t> FindObjectAtPos(const Vector& normalizedPos) const;

private:

	std::unordered_map<size_t, SpaceObjectView> m_objectViews;
};
