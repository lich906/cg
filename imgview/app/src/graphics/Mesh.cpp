#include "graphics/Mesh.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, GLenum usage)
{
	// Bind the Vertex Array Object first, then bind and set vertex and index buffer(s) and attribute pointer(s).
	m_vertexArray.Bind();

	m_vertexBuffer.Bind();
	m_vertexBuffer.SetData(vertices.data(), vertices.size() * sizeof(Vertex), usage);

	m_indexBuffer.Bind();
	m_indexBuffer.SetData(indices.data(), indices.size() * sizeof(GLuint), usage);

	/*
	vertex #1    > vertex #2    > ...
	[x, y][s, t] > [x, y][s, t] > ...
	 |<============>| stride
	 |<======>| vertex size = (vector size + tex coords size)
	*/
	GLsizei stride = sizeof(Vector) + sizeof(TexCoords);

	// Position attribute
	m_vertexArray.BindAttribute(0, GL_FLOAT, sizeof(Vector) / sizeof(float), stride, 0);

	// Texture attribute
	m_vertexArray.BindAttribute(1, GL_FLOAT, sizeof(TexCoords) / sizeof(float), stride, sizeof(Vector));

	//m_vertexBuffer.Unbind();

	// ! Do not unbind m_indexBuffer !

	m_vertexArray.Unbind();
}

void Mesh::Draw(GLenum mode)
{
	m_vertexArray.Bind();
	GlCall(glDrawElements(mode, m_indexBuffer.GetSize(), GL_UNSIGNED_INT, 0));
}
