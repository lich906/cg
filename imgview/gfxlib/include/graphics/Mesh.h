#pragma once

#include "pch.h"

#include "Texture.h"
#include "Vertex.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace gfx
{

class Mesh
{
public:
	Mesh(const std::vector<Vertex>& vertices,
		const std::vector<GLuint>& indices,
		GLenum usage = GL_STATIC_DRAW);

	void Draw(GLenum mode = GL_TRIANGLES);

private:
	VertexArray m_vertexArray;
	VertexBuffer m_vertexBuffer;
	IndexBuffer m_indexBuffer;
};

} // namespace gfx
