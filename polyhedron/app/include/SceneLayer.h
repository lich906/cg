#pragma once

#include <optional>
#include <fstream>

#include "core/core.h"
#include "graphics/Mesh.h"
#include "graphics/Program.h"

#include "Object.h"

class SceneLayer : public core::Layer
{
public:
	SceneLayer();

	// Inherited via core::Layer
	virtual void OnAttach();
	virtual void OnDetach();
	virtual void OnUpdate(core::Timestep ts);
	virtual void OnEvent(core::event::Event& event);

private:
	void LayerOnEvent(core::event::Event& event);

	std::vector<std::unique_ptr<Object>> m_objects;
	glm::mat4 m_polyhedronTransform = glm::mat4(1.0f);
	gfx::Program m_lightProgram;
};
