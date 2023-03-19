#include "opengl_abstractions/VertexArrayObject.h"

VertexArrayObject::VertexArrayObject(const std::vector<Vertex>& vertices, GLenum usage)
	: m_buffer(vertices.data(), vertices.size() * sizeof(Vertex), usage)
{
	glGenVertexArrays(1, &m_objectId);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(m_objectId);
	m_buffer.Bind();

	// Position attribute
	GLsizei stride = (Vector::Size + Color::Size + TextureCoords::Size) * sizeof(GLfloat);
	glVertexAttribPointer(0, Vector::Size, GL_FLOAT, GL_FALSE, stride, (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Color attribute
	glVertexAttribPointer(1, Color::Size, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(Vector::Size * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// Texture attribute
	glVertexAttribPointer(2, TextureCoords::Size, GL_FLOAT, GL_FALSE, stride, (GLvoid*)((Vector::Size + Color::Size) * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	m_buffer.Unbind();

	glBindVertexArray(0); // Unbind VAO
}

void VertexArrayObject::Draw(GLenum mode)
{
	const int count = m_buffer.GetSize() / sizeof(Vertex);

	glBindVertexArray(m_objectId);
	glDrawArrays(mode, 0, count);
	glBindVertexArray(0);
}

void VertexArrayObject::UpdateVerticesData(const std::vector<Vertex>& vertices)
{
	m_buffer.UpdateBufferData(vertices.data(), vertices.size() * sizeof(Vertex));
}

VertexArrayObject::~VertexArrayObject()
{
	glDeleteVertexArrays(1, &m_objectId);
}
