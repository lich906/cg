#pragma once

#include "core/Layer.h"
#include "ParticlesModel.h"
#include "IParticlesLayer.h"
#include "EventController.h"

class ParticlesLayer : public core::Layer, private IParticlesLayer
{
public:
	ParticlesLayer(ParticlesModel& model);

private:
	virtual void OnUpdate(core::Timestep timestep) override;
	virtual void OnEvent(core::event::Event& event) override;

	// Inherited via IParticlesLayer
	virtual void AddParticleView(std::unique_ptr<ParticleView>&& particleView) override;
	virtual void RemoveAllParticleViews() override;

	std::vector<std::unique_ptr<ParticleView>> m_particleViews;
	EventController m_controller;
};
