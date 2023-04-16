#pragma once

#include "core/event/event_inc.h"
#include "ParticlesModel.h"
#include "IParticlesLayer.h"

class EventController
{
public:
	EventController(ParticlesModel& model, IParticlesLayer* layer);

	void OnEvent(core::event::Event& event);
	void OnUpdate(core::Timestep timestep);

private:
	void DispatchMouseMove(core::event::EventDispatcher& dispatcher);
	void DispatchMouseButtonPressed(core::event::EventDispatcher& dispatcher);
	void DispatchKeyPressed(core::event::EventDispatcher& dispatcher);
	void AddPositiveParticle();
	void AddNegativeParticle();

	ParticlesModel& m_model;
	IParticlesLayer* m_layer;

	gfx::Vector m_lastCursorPos;
};
