#pragma once

#include "core/core.h"
#include "Scene.h"

class ImGuiOverlay : public core::Layer
{
public:
	ImGuiOverlay(Scene& scene);

private:
	// Inherited via core::Layer
	virtual void OnAttach();
	virtual void OnDetach();
	virtual void OnUpdate(core::Timestep ts);

	void OnRender();

	Scene& m_scene;
};
