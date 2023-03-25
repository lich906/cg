#pragma once

#include "glad_glfw.h"
#include "graphics/GL/GC.h"
#include "graphics/VertexBuffer.h"
#include "graphics/IndexBuffer.h"

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
	static GL::GC gc;
	GLuint m_obj;
};
