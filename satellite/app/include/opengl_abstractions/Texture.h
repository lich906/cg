#pragma once

#include <glad/glad.h>
#include <string>

class Texture
{
public:
	Texture(const std::string& filePath);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

private:
	static inline GLuint nextRendererId = 0;

	GLuint m_rendererId;
	std::string m_filePath;
	unsigned char* m_localBuffer;
	int m_width, m_height, m_bpp; // bytes per pixel
};
