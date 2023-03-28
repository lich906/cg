#include "view_model/SpaceObjectView.h"

SpaceObjectView::SpaceObjectView(const gfx::Vector& pos, float scale, const gfx::Texture& texture)
	: m_texture(texture)
	, m_scale(scale)
{
}

std::unique_ptr<SpaceObjectView> SpaceObjectView::Create(const gfx::Vector& position, float scale, const gfx::Texture& texture)
{
	auto instance = new SpaceObjectView(position, scale, texture);
	return std::unique_ptr<SpaceObjectView>(instance);
}

void SpaceObjectView::OnSpaceObjectMove(const gfx::Vector& pos)
{
	auto trans = glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, 0.0f));
	Transform(glm::scale(trans, glm::vec3(m_scale, m_scale, 1.0f)));
}

void SpaceObjectView::DoDraw(int width, int height)
{
	m_texture.Bind();
	m_mesh.Draw();
}

void SpaceObjectView::OnVelocityChange(const gfx::Vector& value)
{
	// TODO: handle velocity changes
}
