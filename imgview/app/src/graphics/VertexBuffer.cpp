#include "graphics/VertexBuffer.h"

#include <stdexcept>

VertexBuffer::VertexBuffer(const void* data, size_t size, GLenum usage)
	: m_size(size)
{
	GlCall(glGenBuffers(1, &m_bufferId));
	GlCall(glBindBuffer(GL_ARRAY_BUFFER, m_bufferId));
	GlCall(glBufferData(GL_ARRAY_BUFFER, m_size, data, usage));
	GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

VertexBuffer::~VertexBuffer()
{
	GlCall(glDeleteBuffers(1, &m_bufferId));
}

void VertexBuffer::Bind() const
{
	GlCall(glBindBuffer(GL_ARRAY_BUFFER, m_bufferId));
}

void VertexBuffer::Unbind() const
{
	GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

size_t VertexBuffer::GetSize() const
{
	return m_size;
}

void VertexBuffer::UpdateBufferData(const void* data, size_t size) const
{
	if (size != m_size)
	{
		throw std::logic_error("Buffer size is different.");
	}

	GlCall(glBindBuffer(GL_ARRAY_BUFFER, m_bufferId));
	GlCall(glBufferSubData(GL_ARRAY_BUFFER, 0, m_size, data));
	GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
