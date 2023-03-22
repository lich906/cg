#include "graphics/Texture.h"
#include "../vendor/stb_image/stb_image.h"

Texture::Texture(const std::string& filePath)
	: m_filePath(filePath)
	, m_localBuffer(nullptr)
	, m_width(0)
	, m_height(0)
	, m_bpp(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_localBuffer = stbi_load(m_filePath.c_str(), &m_width, &m_height, &m_bpp, 4);

	glGenTextures(1, &m_rendererId);
	glBindTexture(GL_TEXTURE_2D, m_rendererId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture

	if (m_localBuffer)
		stbi_image_free(m_localBuffer);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_rendererId);
}

void Texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_rendererId);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

int Texture::GetWidth() const
{
	return m_width;
}

int Texture::GetHeight() const
{
	return m_height;
}
