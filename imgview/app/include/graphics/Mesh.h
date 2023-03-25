#pragma once

#include "glad_glfw.h"

#include <vector>

#include "graphics/Texture.h"
#include "graphics/Vertex.h"
#include "graphics/VertexArray.h"
#include "graphics/VertexBuffer.h"
#include "graphics/IndexBuffer.h"

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
