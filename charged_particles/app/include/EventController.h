#pragma once

#include "core/core.h"
#include "core/utils/OrthographicCamera.h"
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
	void UpdateLastCursorPos(float x, float y);
	void OnViewMatrixChange(const glm::mat4& vm);

	core::utils::OrthographicCamera m_camera;

	ParticlesModel& m_model;
	IParticlesLayer* m_layer;

	glm::vec2 m_lastCursorPos;
};
