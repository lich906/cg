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
	// Inherited via Layer
	virtual void OnAttach() override;
	virtual void OnUpdate(core::Timestep timestep) override;
	virtual void OnEvent(core::event::Event& event) override;

	// Inherited via IParticlesLayer
	virtual void AddParticleView(std::unique_ptr<ParticleView>&& particleView) override;
	virtual void RemoveAllParticleViews() override;
	virtual void RemoveParticleView(ParticleView* viewPtr) override;
	virtual gfx::Program& GetProgram() override;

	void OnDraw();
	void DispatchWindowResizeEvent(core::event::Event& event) const;
	void UpdateProjectionMatrixAndViewport(int width, int height) const;

	std::vector<std::unique_ptr<ParticleView>> m_particleViews;
	EventController m_controller;
	gfx::Program m_program;
};
