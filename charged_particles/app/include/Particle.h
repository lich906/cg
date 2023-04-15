#pragma once

#include <boost/signals2.hpp>
#include "graphics/Vector.h"
#include "ParticleType.h"
#include "core/Timestep.h"

constexpr float TIME_SPEED = 0.005f;

using VectorSignal = boost::signals2::signal<void(const gfx::Vector&)>;

class Particle
{
public:
	Particle(ParticleType type, const gfx::Vector& position);

	boost::signals2::connection SubscribeOnMove(const VectorSignal::slot_type& slot);
	inline gfx::Vector GetPosition() { return m_position; }
	void OnUpdate(core::Timestep timestep);
	void SetVelocity(const gfx::Vector& v) { m_velocity = v; }

private:
	gfx::Vector m_position;
	gfx::Vector m_velocity;
	ParticleType m_type;
	VectorSignal m_moveSignal;
};
