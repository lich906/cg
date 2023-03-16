#include "opengl_abstractions/VertexArrayObjectWrapper.h"

#include <iostream>

VertexArrayObjectWrapper::VertexArrayObjectWrapper(const std::vector<Vertex>& vertices, GLenum usage)
	: m_bufferSize(vertices.size() * sizeof(Vertex))
{
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_bufferSize, vertices.data(), usage);

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

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0); // Unbind VAO
}

VertexArrayObjectWrapper::VertexArrayObjectWrapper(VertexArrayObjectWrapper&& other) noexcept
	: m_bufferSize(0)
	, m_vao(0)
	, m_vbo(0)
{
	if (this != &other)
	{
		std::swap(m_bufferSize, other.m_bufferSize);
		std::swap(m_vao, other.m_vao);
		std::swap(m_vbo, other.m_vbo);
	}
}

VertexArrayObjectWrapper& VertexArrayObjectWrapper::operator=(VertexArrayObjectWrapper&& other) noexcept
{
	if (this != &other)
	{
		std::swap(m_bufferSize, other.m_bufferSize);
		std::swap(m_vao, other.m_vao);
		std::swap(m_vbo, other.m_vbo);
	}

	return *this;
}

void VertexArrayObjectWrapper::Draw(GLenum mode)
{
	const int count = m_bufferSize / sizeof(Vertex);

	glBindVertexArray(m_vao);
	glDrawArrays(mode, 0, count);
	glBindVertexArray(0);
}

void VertexArrayObjectWrapper::UpdateVerticesData(const std::vector<Vertex>& vertices)
{
	if (vertices.size() * sizeof(Vertex) != m_bufferSize)
	{
		throw std::logic_error("Vertices count is different.");
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_bufferSize, vertices.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexArrayObjectWrapper::~VertexArrayObjectWrapper()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
}
