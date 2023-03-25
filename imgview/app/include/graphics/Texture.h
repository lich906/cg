#pragma once

#include <string>

#include "glad_glfw.h"
#include "GL/GC.h"

class Texture
{
public:
	Texture(const std::string& filePath, GLint wrappingMode = GL_CLAMP_TO_EDGE);
	~Texture();

	Texture(const Texture& other);
	Texture& operator=(const Texture& other);

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	int GetWidth() const;
	int GetHeight() const;

private:
	inline static GL::GC gc;

	GLuint m_rendererId;
	std::string m_filePath;
	unsigned char* m_localBuffer;
	int m_width, m_height, m_bpp; // bytes per pixel
};
