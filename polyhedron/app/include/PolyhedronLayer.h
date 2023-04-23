#pragma once

#include <optional>
#include <fstream>

#include "core/core.h"
#include "graphics/Mesh.h"
#include "graphics/Program.h"

#include "TriangleMeshLoader.h"

class PolyhedronLayer : public core::Layer
{
public:
	PolyhedronLayer();

	// Inherited via core::Layer
	virtual void OnAttach();
	virtual void OnDetach();
	virtual void OnUpdate(core::Timestep ts);

private:

	void LoadMesh();

	gfx::Program m_program;
	std::optional<gfx::Mesh> m_mesh;
};
