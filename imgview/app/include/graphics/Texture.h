#pragma once

#include <string>

#include "glad_glfw.h"
#include "config.h"
#include "GL/GC.h"

class Texture
{
public:
	Texture(const std::string& filePath, GLint wrappingMode = GL_CLAMP_TO_EDGE, GLint filteringMode = GL_NEAREST);
	~Texture();

	Texture(const Texture& other);
	Texture& operator=(const Texture& other);

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	int GetWidth() const;
	int GetHeight() const;

private:
	static inline GL::GC gc;

	GLuint m_rendererId;
	std::string m_filePath;
	unsigned char* m_localBuffer;
	int m_width, m_height, m_bpp; // bytes per pixel
};
