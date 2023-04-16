#include "gfxpch.h"

#include "graphics/Mesh.h"

using namespace gfx;

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, GLenum usage)
{
	// Bind the Vertex Array Object first, then bind and set vertex and index buffer(s) and attribute pointer(s).
	m_vertexArray.Bind();

	m_vertexBuffer.Bind();
	m_vertexBuffer.SetData(vertices.data(), vertices.size() * sizeof(Vertex), usage);

	m_indexBuffer.Bind();
	m_indexBuffer.SetData(indices.data(), indices.size() * sizeof(GLuint), usage);

	/*
	vertex #1                > vertex #2                > ...
	[x, y][r, g, b, a][s, t] > [x, y][r, g, b, a][s, t] > ...
	 |<========================>| stride
	 |<==================>| vertex size = (vector size + color size + tex coords size)
	*/
	GLsizei stride = sizeof(Vertex);

	// Position attribute
	m_vertexArray.BindAttribute(0, GL_FLOAT, sizeof(Vector) / sizeof(float), stride, 0);

	// Color attribute
	m_vertexArray.BindAttribute(1, GL_FLOAT, sizeof(Vertex::Color) / sizeof(float), stride, sizeof(Vector));

	// Texture attribute
	m_vertexArray.BindAttribute(2, GL_FLOAT, sizeof(TexCoords) / sizeof(float), stride, sizeof(Vector) + sizeof(Vertex::Color));

	m_vertexBuffer.Unbind();

	// ! Do not unbind m_indexBuffer !

	m_vertexArray.Unbind();
}

void Mesh::Draw(GLenum mode) const
{
	m_vertexArray.Bind();
	GlCall(glDrawElements(mode, m_indexBuffer.GetSize(), GL_UNSIGNED_INT, 0));
}
