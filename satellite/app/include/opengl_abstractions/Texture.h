#pragma once

#include "glad_glfw.h"

#include <string>

class Texture
{
public:
	Texture(const std::string& filePath);
	~Texture();

	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;
	Texture(Texture&& other) noexcept;
	Texture& operator=(Texture&& other) noexcept;

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

private:
	GLuint m_rendererId;
	std::string m_filePath;
	unsigned char* m_localBuffer;
	int m_width, m_height, m_bpp; // bytes per pixel
};
