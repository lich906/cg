#pragma once

#include "glad_glfw.h"

#include <vector>

#include "Texture.h"
#include "Vertex.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class Mesh
{
public:
	Mesh(const std::vector<Vertex>& vertices,
		const std::vector<GLuint>& indices,
		GLenum usage = GL_STATIC_DRAW);

	~Mesh();

	void Draw(GLenum mode = GL_TRIANGLES);

private:
	GLuint m_vertexArrayId;
	VertexBuffer m_vertexBuffer;
	IndexBuffer m_indexBuffer;
};
