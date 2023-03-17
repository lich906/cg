#include "view_model/SpaceObjectView.h"

#include <iostream>

SpaceObjectView::SpaceObjectView(const Vector& normalizedPos, float scale, Texture texture)
	: m_scale(scale)
	, m_texture(std::move(texture))
// clang-format off
	, m_vertices({
		{ { normalizedPos.x - m_scale, normalizedPos.y + m_scale }, { 0.0f, 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } },
		{ { normalizedPos.x - m_scale, normalizedPos.y - m_scale }, { 0.0f, 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
		{ { normalizedPos.x + m_scale, normalizedPos.y + m_scale }, { 0.0f, 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } },
		{ { normalizedPos.x + m_scale, normalizedPos.y - m_scale }, { 0.0f, 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } }})
// clang-format on
	, m_vaoWrapper(m_vertices, GL_DYNAMIC_DRAW)
{
}

void SpaceObjectView::Draw(int width, int height)
{
	UpdatePosition(width, height);

	m_texture.Bind();
	m_vaoWrapper.Draw(GL_TRIANGLE_STRIP);
}

bool SpaceObjectView::ExistsAtPos(const Vector& normalizedPos) const
{
// clang-format off
	return
		normalizedPos.y >= m_vertices[1].position.y &&
		normalizedPos.y <= m_vertices[0].position.y &&
		normalizedPos.x >= m_vertices[0].position.x &&
		normalizedPos.x <= m_vertices[2].position.x;
	// clang-format on
}

void SpaceObjectView::Move(const Vector& deltaPos)
{
	m_deltaPos += deltaPos;
}

void SpaceObjectView::OnSpaceObjectMove(const Vector& deltaPos)
{
	Move(deltaPos);
}

void SpaceObjectView::UpdatePosition(int width, int height)
{
	if (m_deltaPos)
	{
		Vector normDelta(
			std::min(std::max(-1.0f, 2 * m_deltaPos.x / width), 1.0f),
			std::min(std::max(-1.0f, -(2 * m_deltaPos.y / height)), 1.0f));

		for (auto& vertex : m_vertices)
		{
			vertex.position.x += normDelta.x;
			vertex.position.y += normDelta.y;
		}

		m_vaoWrapper.UpdateVerticesData(m_vertices);

		m_deltaPos.x = m_deltaPos.y = 0.0f;
	}
}
