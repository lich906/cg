#pragma once

#include <glad/glad.h>
#include <vector>
#include <stdexcept>

#include "Vertex.h"

class VertexArrayObjectWrapper
{
public:
	/*
		bufferSize -- exact size of buffer in bytes (use sizeof)
		vertexArrayBuffer -- data itself
		usage -- last argument used in glBufferData(), one of:
			* GL_STATIC_DRAW
			* GL_DYNAMIC_DRAW
			* GL_STREAM_DRAW
	*/
	VertexArrayObjectWrapper(size_t bufferSize, Vertex vertexArrayBuffer[], GLenum usage);

	void Draw(GLenum mode);

	~VertexArrayObjectWrapper() noexcept;

private:
	size_t m_bufferSize;
	GLuint m_vao, m_vbo;
};
