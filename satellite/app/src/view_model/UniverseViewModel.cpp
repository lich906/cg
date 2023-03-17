#include "view_model/UniverseViewModel.h"

void UniverseViewModel::AddNewObjectView(size_t uid, SpaceObjectViewPtr&& objectView)
{
	m_objectViews.emplace(uid, std::move(objectView));
}

void UniverseViewModel::RemoveAllObjectViews()
{
	m_objectViews.clear();
}

void UniverseViewModel::Draw(int width, int height)
{
	for (auto& [id, objView] : m_objectViews)
	{
		objView->Draw(width, height);
	}
}

std::optional<size_t> UniverseViewModel::FindObjectAtPos(const Vector& normalizedPos) const
{
	for (auto& [id, objectView] : m_objectViews)
	{
		if (objectView->ExistsAtPos(normalizedPos))
			return id;
	}

	return std::nullopt;
}

void UniverseViewModel::MoveObjectView(size_t uid, const Vector& deltaPos)
{
	auto objView = m_objectViews.find(uid);

	if (objView != m_objectViews.end())
	{
		objView->second->Move(deltaPos);
	}
}
