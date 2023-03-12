#include "VertexArrayObjectWrapper.h"

VertexArrayObjectWrapper::VertexArrayObjectWrapper(size_t bufferSize, Vertex vertexArrayBuffer[], GLenum usage)
	: m_bufferSize(bufferSize)
{
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_bufferSize, vertexArrayBuffer, usage);

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

	glBindVertexArray(NULL); // Unbind VAO
}

void VertexArrayObjectWrapper::Draw(GLenum mode)
{
	static const int count = m_bufferSize / sizeof(Vertex);

	glBindVertexArray(m_vao);
	glDrawArrays(mode, 0, count);
	glBindVertexArray(NULL);
}

VertexArrayObjectWrapper::~VertexArrayObjectWrapper()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
}
