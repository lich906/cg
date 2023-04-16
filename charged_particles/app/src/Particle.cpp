#include "Particle.h"

Particle::Particle(ParticleType type, const gfx::Vector& position)
	: m_type(type)
	, m_position(position)
{
}

Particle::~Particle()
{
	m_removalSignal();
}

boost::signals2::connection Particle::SubscribeOnMove(const VectorSignal::slot_type& slot)
{
	slot(m_position);
	return m_moveSignal.connect(slot);
}

boost::signals2::connection Particle::SubscribeOnRemoval(const VoidSignal::slot_type& slot)
{
	return m_removalSignal.connect(slot);
}

void Particle::OnUpdate(core::Timestep timestep)
{
	if (m_velocity)
	{
		m_position += m_velocity * timestep * consts::TIME_SPEED;
		m_moveSignal(m_position);
	}
}

void Particle::UpdateVelocity(const gfx::Vector& acc, core::Timestep timestep)
{
	m_velocity += acc * timestep * consts::TIME_SPEED;
}
