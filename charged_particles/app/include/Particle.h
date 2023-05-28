#pragma once

#include <boost/signals2.hpp>
#include <glm/glm.hpp>

#include "ParticleType.h"
#include "core/Timestep.h"
#include "consts.h"

using VectorSignal = boost::signals2::signal<void(const glm::vec2&)>;
using VoidSignal = boost::signals2::signal<void()>;
// добавить гравитационное взаимодействие между частицами
class Particle
{
public:
	Particle(ParticleType type, const glm::vec2& position);
	~Particle();

	boost::signals2::connection SubscribeOnMove(const VectorSignal::slot_type& slot);
	boost::signals2::connection SubscribeOnRemoval(const VoidSignal::slot_type& slot);
	inline ParticleType GetType() const { return m_type; }
	inline glm::vec2 GetPosition() const { return m_position; }
	void OnUpdate(core::Timestep timestep);
	void UpdateVelocity(const glm::vec2& acc, core::Timestep timestep);

private:
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	ParticleType m_type;
	VectorSignal m_moveSignal;
	VoidSignal m_removalSignal;
};
