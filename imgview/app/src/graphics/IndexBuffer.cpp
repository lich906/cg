#include "graphics/IndexBuffer.h"

#include <stdexcept>

IndexBuffer::IndexBuffer(const GLuint* data, size_t size, GLenum usage)
	: m_size(size)
{
	GlCall(glGenBuffers(1, &m_bufferId));
	GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId));
	GlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_size * sizeof(GLuint), data, usage));
	GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

IndexBuffer::~IndexBuffer()
{
	GlCall(glDeleteBuffers(1, &m_bufferId));
}

void IndexBuffer::Bind() const
{
	GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId));
}

void IndexBuffer::Unbind() const
{
	GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
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

	GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId));
	GlCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_size * sizeof(GLuint), data));
	GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
