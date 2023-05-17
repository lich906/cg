#pragma once

#include "graphics/Mesh.h"
#include "Object.h"

class RectangleMesh : public Object
{
public:
	RectangleMesh();

private:
	virtual void OnDraw(gfx::Program& prog) override;

	static std::vector<gfx::Vertex> GetVertices();
	static std::vector<GLuint> GetIndices();

	gfx::Mesh m_mesh;
};
