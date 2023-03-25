#include "graphics/IndexBuffer.h"

#include <stdexcept>

IndexBuffer::IndexBuffer()
	: m_size(0)
{
	GlCall(gc.Create(m_obj, glGenBuffers, glDeleteBuffers));
}

IndexBuffer::IndexBuffer(const IndexBuffer& other)
	: m_size(other.m_size)
{
	gc.Copy(other.m_obj, m_obj);
}

IndexBuffer::IndexBuffer(const void* data, size_t size, GLenum usage)
	: m_size(size)
{
	GlCall(gc.Create(m_obj, glGenBuffers, glDeleteBuffers));
	SetData(data, m_size, usage);
	Unbind();
}

IndexBuffer::~IndexBuffer()
{
	GlCall(gc.Destroy(m_obj));
}

IndexBuffer::operator GLuint() const
{
	return m_obj;
}

const IndexBuffer& IndexBuffer::operator=(const IndexBuffer& other)
{
	gc.Copy(other.m_obj, m_obj, true);
	return *this;
}

void IndexBuffer::Bind() const
{
	GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_obj));
}

void IndexBuffer::Unbind() const
{
	GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

size_t IndexBuffer::GetSize() const
{
	return m_size;
}

void IndexBuffer::SetData(const void* data, size_t size, GLenum usage)
{
	Bind();
	GlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage));
	m_size = size;
}

void IndexBuffer::SetSubData(const void* data, size_t offset, size_t size)
{
	if (size > m_size)
	{
		throw std::logic_error("Data size exceeds current buffer size.");
	}

	Bind();
	GlCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data));
}

void IndexBuffer::GetSubData(void* data, size_t offset, size_t length)
{
	Bind();
	GlCall(glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, length, data));
}

GL::GC IndexBuffer::gc;