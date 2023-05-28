#include "ParticleView.h"

void ParticleView::Observe(Particle& particle)
{
	m_conns += particle.SubscribeOnMove(std::bind(&ParticleView::OnParticleMove, this, std::placeholders::_1));
	m_conns += particle.SubscribeOnRemoval(std::bind(&ParticleView::RemoveSelf, this));
}

void ParticleView::OnDraw(gfx::Program& program) const
{
	program.SetUniformMatrix4fv("m_model", m_transform);
	OnDrawImpl(program);
}

ParticleView::ParticleView(const SelfRemovalFn& removeSelfFn)
	: m_removeSelfFn(removeSelfFn)
	, m_transform(1.0f)
{
}

void ParticleView::OnParticleMove(const glm::vec2& pos)
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, 0.0f));
	transform = glm::scale(transform, glm::vec3(consts::PARTICLE_SCALE, consts::PARTICLE_SCALE, 1.0f));
	m_transform = transform;
}

void ParticleView::RemoveSelf()
{
	m_removeSelfFn(this);
}
