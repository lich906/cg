#pragma once

#include <boost/signals2.hpp>
#include "graphics/Vector.h"
#include "ParticleType.h"
#include "core/Timestep.h"
#include "consts.h"

using VectorSignal = boost::signals2::signal<void(const gfx::Vector&)>;
using VoidSignal = boost::signals2::signal<void()>;

class Particle
{
public:
	Particle(ParticleType type, const gfx::Vector& position);
	~Particle();

	boost::signals2::connection SubscribeOnMove(const VectorSignal::slot_type& slot);
	boost::signals2::connection SubscribeOnRemoval(const VoidSignal::slot_type& slot);
	inline ParticleType GetType() const { return m_type; }
	inline gfx::Vector GetPosition() const { return m_position; }
	void OnUpdate(core::Timestep timestep);
	void UpdateVelocity(const gfx::Vector& acc, core::Timestep timestep);

private:
	gfx::Vector m_position;
	gfx::Vector m_velocity;
	ParticleType m_type;
	VectorSignal m_moveSignal;
	VoidSignal m_removalSignal;
};
