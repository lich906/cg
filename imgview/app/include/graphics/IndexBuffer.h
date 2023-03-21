#pragma once

#include "glad_glfw.h"

class IndexBuffer
{
public:
	IndexBuffer(const GLuint* data, size_t size, GLenum usage);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	size_t GetSize() const;

	void UpdateBufferData(const void* data, size_t size) const;

private:
	GLuint m_bufferId;
	size_t m_size;
};
