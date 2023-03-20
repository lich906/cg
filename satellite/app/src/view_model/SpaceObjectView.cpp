#include "view_model/SpaceObjectView.h"

SpaceObjectView::SpaceObjectView(const Vector& pos, float scale, Texture&& texture)
	: m_texture(std::move(texture))
// clang-format off
	, m_vertices({
		{ { pos.x - scale, pos.y - scale }, { 0.0f, 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } },
		{ { pos.x - scale, pos.y + scale }, { 0.0f, 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
		{ { pos.x + scale, pos.y - scale }, { 0.0f, 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } },
		{ { pos.x + scale, pos.y + scale }, { 0.0f, 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } }})
// clang-format on
	, m_vaoWrapper(m_vertices, GL_DYNAMIC_DRAW)
{
}

SpaceObjectViewPtr SpaceObjectView::Create(const Vector& position, float scale, Texture&& texture)
{
	auto instance = new SpaceObjectView(position, scale, std::move(texture));
	return std::unique_ptr<SpaceObjectView>(instance);
}

void SpaceObjectView::Draw(int width, int height)
{
	UpdatePosition(width, height);

	m_texture.Bind();
	m_vaoWrapper.Draw(GL_TRIANGLE_STRIP);
}

bool SpaceObjectView::ExistsAtPos(const Vector& pos) const
{
// clang-format off
	return
		pos.y <= m_vertices[1].position.y &&
		pos.y >= m_vertices[0].position.y &&
		pos.x >= m_vertices[0].position.x &&
		pos.x <= m_vertices[2].position.x;
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
		for (auto& vertex : m_vertices)
		{
			vertex.position += m_deltaPos;
		}

		m_vaoWrapper.UpdateVerticesData(m_vertices);

		m_deltaPos.x = m_deltaPos.y = 0.0f;
	}
}
