#pragma once

#include "glad_glfw.h"
#include "GL/GC.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

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
