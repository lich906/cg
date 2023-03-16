#pragma once

#include "glad_glfw.h"

#include <vector>
#include <stdexcept>

#include "types/Vertex.h"

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
	VertexArrayObjectWrapper(const std::vector<Vertex>& vertices, GLenum usage);

	VertexArrayObjectWrapper(const VertexArrayObjectWrapper&) = delete;
	VertexArrayObjectWrapper& operator=(const VertexArrayObjectWrapper&) = delete;
	VertexArrayObjectWrapper(VertexArrayObjectWrapper&& other) noexcept;
	VertexArrayObjectWrapper& operator=(VertexArrayObjectWrapper&& other) noexcept;

	void Draw(GLenum mode);

	void UpdateVerticesData(const std::vector<Vertex>& vertices);

	~VertexArrayObjectWrapper() noexcept;

private:
	size_t m_bufferSize;
	GLuint m_vao, m_vbo;
};
