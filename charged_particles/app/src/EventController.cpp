#include "EventController.h"

EventController::EventController(ParticlesModel& model, IParticlesLayer* layer)
	: m_model(model)
	, m_layer(layer)
{
}

void EventController::OnEvent(core::event::Event& event)
{
	// TODO: dispatch user events
}

void EventController::OnUpdate(core::Timestep timestep)
{
	m_model.OnUpdate(timestep);
}
