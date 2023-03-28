#pragma once

#include "pch.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace gfx
{

class VertexArray
{
public:
	VertexArray();
	VertexArray(const VertexArray& other);

	~VertexArray();

	void Bind();
	void Unbind();

	operator GLuint() const;
	const VertexArray& operator=(const VertexArray& other);

	void BindAttribute(GLint location, GLenum type, GLuint count, GLuint stride, intptr_t offset);

private:
	static inline GL::GC gc;
	GLuint m_obj;
};

} // namespace gfx
