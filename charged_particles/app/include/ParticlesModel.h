#pragma once

#include <memory>

#include "Particle.h"

class ParticlesModel
{
public:

	void AddParticle(std::unique_ptr<Particle>&& particle);
	void RemoveAllParticles();
	void OnUpdate(core::Timestep timestep);

private:
	std::vector<std::unique_ptr<Particle>> m_particles;
};
