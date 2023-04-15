#pragma once

#include "core/event/Event.h"
#include "ParticlesModel.h"
#include "IParticlesLayer.h"

class EventController
{
public:
	EventController(ParticlesModel& model, IParticlesLayer* layer);

	void OnEvent(core::event::Event& event);
	void OnUpdate(core::Timestep timestep);

private:
	ParticlesModel& m_model;
	IParticlesLayer* m_layer;
};
