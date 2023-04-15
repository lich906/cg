#include "ParticlesModel.h"

void ParticlesModel::AddParticle(std::unique_ptr<Particle>&& particle)
{
	m_particles.emplace_back(std::move(particle));
}

void ParticlesModel::RemoveAllParticles()
{
	m_particles.clear();
}

void ParticlesModel::OnUpdate(core::Timestep timestep)
{
	// TODO: implement model update
}
