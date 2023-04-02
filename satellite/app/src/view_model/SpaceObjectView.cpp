#include "view_model/SpaceObjectView.h"

SpaceObjectView::SpaceObjectView(const gfx::Vector& pos, float scale, const gfx::Texture& texture)
	: m_texture(texture)
	, m_scale(scale)
	, m_arrow(pos)
{
	glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, 0.0f));
	Transform(glm::scale(trans, glm::vec3(m_scale, m_scale, 1.0f)));
}

std::unique_ptr<SpaceObjectView> SpaceObjectView::Create(const gfx::Vector& position, float scale, const gfx::Texture& texture)
{
	auto instance = new SpaceObjectView(position, scale, texture);
	return std::unique_ptr<SpaceObjectView>(instance);
}

void SpaceObjectView::Observe(SpaceObject& spaceObject)
{
	spaceObject.RegisterPositionObs([this](const gfx::Vector& v) { OnSpaceObjectMove(v); }, true);
	spaceObject.RegisterVelocityObs([this](const gfx::Vector& v) { OnVelocityChange(v); }, true);
	spaceObject.RegisterDeletionObs([this]() { RemoveSelf(); });
}

void SpaceObjectView::OnSpaceObjectMove(const gfx::Vector& pos)
{
	auto trans = glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, 0.0f));
	Transform(glm::scale(trans, glm::vec3(m_scale, m_scale, 1.0f)));
	m_arrow.SetStartPoint(pos);
}

void SpaceObjectView::DoDraw(int width, int height)
{
	m_texture.Bind();
	m_mesh.Draw();
	m_arrow.Draw(width, height);
}

void SpaceObjectView::OnVelocityChange(const gfx::Vector& v)
{
	m_arrow.SetDirection(v);
}
