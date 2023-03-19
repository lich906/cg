#pragma once

#include "glad_glfw.h"

#include <vector>
#include <stdexcept>

#include "types/Vertex.h"
#include "VertexBuffer.h"

class VertexArrayObject
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
	VertexArrayObject(const std::vector<Vertex>& vertices, GLenum usage);

	VertexArrayObject(const VertexArrayObject&) = delete;
	VertexArrayObject& operator=(const VertexArrayObject&) = delete;
	VertexArrayObject(VertexArrayObject&&) = default;
	VertexArrayObject& operator=(VertexArrayObject&&) = default;

	void Draw(GLenum mode);

	void UpdateVerticesData(const std::vector<Vertex>& vertices);

	~VertexArrayObject() noexcept;

private:
	GLuint m_objectId;
	VertexBuffer m_buffer;
};
