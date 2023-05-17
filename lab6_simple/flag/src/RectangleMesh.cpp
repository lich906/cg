#include "RectangleMesh.h"

RectangleMesh::RectangleMesh()
	: m_mesh(GetVertices(), GetIndices())
{
}

void RectangleMesh::OnDraw(gfx::Program& prog)
{
	m_mesh.Draw(GL_TRIANGLE_STRIP);
}

std::vector<gfx::Vertex> RectangleMesh::GetVertices()
{
	return {
		gfx::Vertex{ { -1.0f,  0.6666f, 1.0f }, {}, {} },
		gfx::Vertex{ { -1.0f, -0.6666f, 1.0f }, {}, {} },
		gfx::Vertex{ {  1.0f,  0.6666f, 1.0f }, {}, {} },
		gfx::Vertex{ {  1.0f, -0.6666f, 1.0f }, {}, {} }
	};
}

std::vector<GLuint> RectangleMesh::GetIndices()
{
	return { 0u, 1u, 2u, 3u };
}
