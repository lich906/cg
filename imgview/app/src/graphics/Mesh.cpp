#include "graphics/Mesh.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, GLenum usage)
	: m_vertexBuffer(vertices.data(), vertices.size() * sizeof(Vertex), usage)
	, m_indexBuffer(indices.data(), indices.size(), usage)
{
	glGenVertexArrays(1, &m_vertexArrayId);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(m_vertexArrayId);
	m_vertexBuffer.Bind();
	m_indexBuffer.Bind();

	// Position attribute
	GLsizei stride = (Vector::Size + TexCoords::Size) * sizeof(GLfloat);
	glVertexAttribPointer(0, Vector::Size, GL_FLOAT, GL_FALSE, stride, (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Texture attribute
	glVertexAttribPointer(1, TexCoords::Size, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(Vector::Size * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	m_vertexBuffer.Unbind();

	glBindVertexArray(0); // Unbind VAO		!Do not unbind EBO!
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vertexArrayId);
}

void Mesh::Render(GLenum mode)
{
	glBindVertexArray(m_vertexArrayId);
	glDrawElements(mode, m_indexBuffer.GetSize(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
