#include "graphics/Mesh.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, GLenum usage)
	: m_vertexBuffer(vertices.data(), vertices.size() * sizeof(Vertex), usage)
	, m_indexBuffer(indices.data(), indices.size(), usage)
{
	GlCall(glGenVertexArrays(1, &m_vertexArrayId));

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	GlCall(glBindVertexArray(m_vertexArrayId));
	m_vertexBuffer.Bind();
	m_indexBuffer.Bind();

	// Position attribute
	GLsizei stride = (Vector::Size + TexCoords::Size) * sizeof(GLfloat);
	GlCall(glVertexAttribPointer(0, Vector::Size, GL_FLOAT, GL_FALSE, stride, (GLvoid*)0));
	GlCall(glEnableVertexAttribArray(0));

	// Texture attribute
	GlCall(glVertexAttribPointer(1, TexCoords::Size, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(Vector::Size * sizeof(GLfloat))));
	GlCall(glEnableVertexAttribArray(1));

	m_vertexBuffer.Unbind();

	GlCall(glBindVertexArray(0)); // Unbind VAO		!Do not unbind EBO!
}

Mesh::~Mesh()
{
	GlCall(glDeleteVertexArrays(1, &m_vertexArrayId));
}

void Mesh::Draw(GLenum mode)
{
	GlCall(glBindVertexArray(m_vertexArrayId));
	GlCall(glDrawElements(mode, m_indexBuffer.GetSize(), GL_UNSIGNED_INT, 0));
	GlCall(glBindVertexArray(0));
}
