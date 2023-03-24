#include <stdexcept>

#include "graphics/Texture.h"
#include "../vendor/stb_image/stb_image.h"

Texture::Texture(const std::string& filePath, GLint wrappingMode)
	: m_filePath(filePath)
	, m_localBuffer(nullptr)
	, m_width(0)
	, m_height(0)
	, m_bpp(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_localBuffer = stbi_load(m_filePath.c_str(), &m_width, &m_height, &m_bpp, 4);

	if (!m_localBuffer)
	{
		throw std::runtime_error("Failed to open image.");
	}

	GlCall(glGenTextures(1, &m_rendererId));
	GlCall(glBindTexture(GL_TEXTURE_2D, m_rendererId));

	GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrappingMode));
	GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrappingMode));

	GlCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer));
	GlCall(glGenerateMipmap(GL_TEXTURE_2D));

	GlCall(glBindTexture(GL_TEXTURE_2D, 0)); // Unbind texture

	if (m_localBuffer)
		stbi_image_free(m_localBuffer);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_rendererId);
}

void Texture::Bind(unsigned int slot) const
{
	GlCall(glActiveTexture(GL_TEXTURE0 + slot));
	GlCall(glBindTexture(GL_TEXTURE_2D, m_rendererId));
}

void Texture::Unbind() const
{
	GlCall(glBindTexture(GL_TEXTURE_2D, 0));
}

int Texture::GetWidth() const
{
	return m_width;
}

int Texture::GetHeight() const
{
	return m_height;
}
