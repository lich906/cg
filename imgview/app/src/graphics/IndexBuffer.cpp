#include "graphics/IndexBuffer.h"

#include <stdexcept>

IndexBuffer::IndexBuffer(const GLuint* data, size_t size, GLenum usage)
	: m_size(size)
{
	glGenBuffers(1, &m_bufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_size * sizeof(GLuint), data, usage);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_bufferId);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

size_t IndexBuffer::GetSize() const
{
	return m_size;
}

void IndexBuffer::UpdateBufferData(const void* data, size_t size) const
{
	if (size != m_size)
	{
		throw std::logic_error("Buffer size is different.");
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_size * sizeof(GLuint), data);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
