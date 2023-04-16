#pragma once

#include <memory>

#include "Particle.h"
#include "consts.h"

class ParticlesModel
{
public:

	void AddParticle(std::unique_ptr<Particle>&& particle);
	void RemoveAllParticles();
	bool RemoveParticleAtPosIfExists(const gfx::Vector& pos); /* Return 'true' if particle was removed. */
	void OnUpdate(core::Timestep timestep);

private:
	std::vector<gfx::Vector> GetParticlesAcceleration() const;
	std::pair<gfx::Vector, gfx::Vector> GetDipoleAccelerationImpact(const Particle& first, const Particle& second) const;

	std::vector<std::unique_ptr<Particle>> m_particles;
};
