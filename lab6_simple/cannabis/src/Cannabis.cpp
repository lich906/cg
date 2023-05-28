#include "Cannabis.h"

Cannabis::Cannabis()
	: m_mesh(GenerateVertices(), GenerateIndices())
{
}

void Cannabis::OnDraw(gfx::Program& prog)
{
	GlCall(glPointSize(3.0f));
	m_mesh.Draw(GL_LINE_LOOP);
	GlCall(glPointSize(1.0f));
}

std::vector<gfx::Vertex> Cannabis::GenerateVertices()
{
	std::vector<gfx::Vertex> vertices;

	for (float x = X_MIN; x <= X_MAX; x += X_STEP)
	{
		vertices.push_back(gfx::Vertex{ { x, x, 1.0f }, {}, {}, {} });
	}

	return vertices;
}

std::vector<GLuint> Cannabis::GenerateIndices()
{
	std::vector<GLuint> indices;
	GLuint index = 0;

	for (float x = X_MIN; x <= X_MAX; x += X_STEP)
	{
		indices.push_back(index++);
	}

	return indices;
}
