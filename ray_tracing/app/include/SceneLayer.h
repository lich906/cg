#pragma once

#include "core/core.h"
#include "graphics/Mesh.h"
#include "graphics/Program.h"

#include "Renderer.h"

class SceneLayer : public core::Layer
{
public:
	SceneLayer();

private:
	// Inherited via Layer
	virtual void OnAttach() override;
	virtual void OnUpdate(core::Timestep ts) override;
	virtual void OnEvent(core::event::Event& event) override;

	bool OnResize(core::event::WindowResizeEvent& e);

	Camera m_camera;
	Scene m_scene;
	Renderer m_renderer;

	gfx::Program m_shader;
	bool m_firstFrame = true;
};
