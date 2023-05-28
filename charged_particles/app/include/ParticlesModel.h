#pragma once

#include <memory>

#include "Particle.h"
#include "consts.h"

class ParticlesModel
{
public:

	void AddParticle(std::unique_ptr<Particle>&& particle);
	void RemoveAllParticles();
	bool RemoveParticleAtPosIfExists(const glm::vec2& pos); /* Return 'true' if particle was removed. */
	void OnUpdate(core::Timestep timestep);

private:
	std::vector<glm::vec2> GetParticlesAcceleration() const;
	std::pair<glm::vec2, glm::vec2> GetDipoleAccelerationImpact(const Particle& first, const Particle& second) const;

	std::vector<std::unique_ptr<Particle>> m_particles;
};
