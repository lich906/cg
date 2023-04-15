#include "ParticlesLayer.h"

ParticlesLayer::ParticlesLayer(ParticlesModel& model)
	: m_controller(model, this)
{
}

void ParticlesLayer::OnUpdate(core::Timestep timestep)
{
	m_controller.OnUpdate(timestep);
}

void ParticlesLayer::OnEvent(core::event::Event& event)
{
	m_controller.OnEvent(event);
}

void ParticlesLayer::AddParticleView(std::unique_ptr<ParticleView>&& particleView)
{
	m_particleViews.emplace_back(std::move(particleView));
}

void ParticlesLayer::RemoveAllParticleViews()
{
	m_particleViews.clear();
}
