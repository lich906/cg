#include "opengl_abstractions/VertexBuffer.h"
#include <stdexcept>

VertexBuffer::VertexBuffer(const void* data, size_t size, GLenum usage)
	: m_bufferSize(size)
{
	glGenBuffers(1, &m_bufferId);
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);
	glBufferData(GL_ARRAY_BUFFER, m_bufferSize, data, usage);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_bufferId);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

size_t VertexBuffer::GetSize() const
{
	return m_bufferSize;
}

void VertexBuffer::UpdateBufferData(const void* data, size_t size) const
{
	if (size != m_bufferSize)
	{
		throw std::logic_error("Vertices count is different.");
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_bufferSize, data);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
