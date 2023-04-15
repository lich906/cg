#include "Particle.h"

Particle::Particle(ParticleType type, const gfx::Vector& position)
	: m_type(type)
	, m_position(position)
{
}

boost::signals2::connection Particle::SubscribeOnMove(const VectorSignal::slot_type& slot)
{
	slot(m_position);
	return m_moveSignal.connect(slot);
}

void Particle::OnUpdate(core::Timestep timestep)
{
	if (m_velocity)
	{
		m_position += m_velocity * timestep * TIME_SPEED;
		m_moveSignal(m_position);
	}
}
