#pragma once

#include "glad_glfw.h"
#include "graphics/GL/GC.h"

class IndexBuffer
{
public:
	IndexBuffer();
	IndexBuffer(const IndexBuffer& other);
	IndexBuffer(const void* data, size_t size, GLenum usage);

	~IndexBuffer();

	operator GLuint() const;
	const IndexBuffer& operator=(const IndexBuffer& other);

	void Bind() const;
	void Unbind() const;

	size_t GetSize() const;

	void SetData(const void* data, size_t size, GLenum usage);
	void SetSubData(const void* data, size_t offset, size_t size);

	void GetSubData(void* data, size_t offset, size_t size);

private:
	static inline GL::GC gc;
	GLuint m_obj;
	size_t m_size;
};
