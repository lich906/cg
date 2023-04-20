#include "ParticlesModel.h"

void ParticlesModel::AddParticle(std::unique_ptr<Particle>&& particle)
{
	m_particles.emplace_back(std::move(particle));
}

void ParticlesModel::RemoveAllParticles()
{
	m_particles.clear();
}

bool ParticlesModel::RemoveParticleAtPosIfExists(const gfx::Vector& pos)
{
	auto it = std::find_if(m_particles.begin(), m_particles.end(),
		[&](const std::unique_ptr<Particle>& particle) {
			auto particlePos = particle->GetPosition();
			return (pos - particlePos).Mod() <= consts::PARTICLE_SCALE / 2;
		});

	if (it != m_particles.end())
	{
		m_particles.erase(it);
		return true;
	}

	return false;
}

void ParticlesModel::OnUpdate(core::Timestep timestep)
{
	auto particlesAcc = GetParticlesAcceleration();

	for (size_t index = 0; index < m_particles.size(); ++index)
	{
		m_particles[index]->UpdateVelocity(particlesAcc[index], timestep);
	}

	for (auto& particle : m_particles)
	{
		particle->OnUpdate(timestep);
	}
}

std::vector<gfx::Vector> ParticlesModel::GetParticlesAcceleration() const
{
	std::vector<gfx::Vector> particlesAcc(m_particles.size());
	
	for (size_t targetIdx = 0; targetIdx < m_particles.size(); ++targetIdx)
	{
		auto& targetParticle = m_particles[targetIdx];

		for (size_t otherIdx = targetIdx + 1; otherIdx < m_particles.size(); ++otherIdx)
		{
			gfx::Vector targetAcc, otherAcc;
			std::tie(targetAcc, otherAcc) = GetDipoleAccelerationImpact(*targetParticle, *m_particles[otherIdx]);
			particlesAcc[targetIdx] += targetAcc;
			particlesAcc[otherIdx] += otherAcc;
		}
	}

	return particlesAcc;
}

std::pair<gfx::Vector, gfx::Vector> ParticlesModel::GetDipoleAccelerationImpact(const Particle& first, const Particle& second) const
{
	gfx::Vector v = second.GetPosition() - first.GetPosition();
	float d = v.Mod();
	gfx::Vector r = v / d;
	float forceMagnitude = consts::COLOUMB_LAW_CONSTANT / (d * d);

	if (first.GetType() == second.GetType())
	{
		forceMagnitude -= consts::GRAV_CONSTANT / (d * d);
		forceMagnitude += consts::REPULSION_COEFF / (d * d * d);
		return { -r * forceMagnitude, r * forceMagnitude };
	}
	else
	{
		forceMagnitude += consts::GRAV_CONSTANT / (d * d);
		forceMagnitude -= consts::REPULSION_COEFF / (d * d * d);
		return { r * forceMagnitude, -r * forceMagnitude };
	}
}
