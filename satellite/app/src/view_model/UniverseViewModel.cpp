#include "view_model/UniverseViewModel.h"

#include <iostream>

void UniverseViewModel::AddNewObjectView(size_t uid, SpaceObjectView&& objectView)
{
	m_objectViews.emplace(uid, std::forward<SpaceObjectView>(objectView));
}

void UniverseViewModel::RemoveAllObjectViews()
{
	m_objectViews.clear();
}

void UniverseViewModel::Draw(int width, int height)
{
	for (auto& [id, objView] : m_objectViews)
	{
		objView.Draw(width, height);
	}
}

std::optional<size_t> UniverseViewModel::FindObjectAtPos(const Vector& normalizedPos) const
{
	for (auto& [id, objectView] : m_objectViews)
	{
		if (objectView.ExistsAtPos(normalizedPos))
			return id;
	}

	return std::nullopt;
}
