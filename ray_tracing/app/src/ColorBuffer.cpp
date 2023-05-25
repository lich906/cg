#include <cstring>
#include <stdexcept>

#include "ColorBuffer.h"

ColorBuffer::~ColorBuffer()
{
	std::free(m_data);
}

void ColorBuffer::Resize(uint32_t width, uint32_t height)
{
	if (!m_data)
	{
		m_data = reinterpret_cast<Color*>(std::calloc(width * height, sizeof(Color)));
	}

	void* ptr = std::realloc(m_data, width * height * sizeof(Color));
	if (!ptr)
		throw std::runtime_error("Failed to allocate memory");
	m_data = reinterpret_cast<Color*>(ptr);
	m_width = width;
	m_height = height;
}

const void* ColorBuffer::GetData() const
{
	return &m_data[0].r;
}

size_t ColorBuffer::GetSizeInBytes() const
{
	return m_width * m_height * sizeof(Color);
}

size_t ColorBuffer::GetWidth() const
{
	return m_width;
}

size_t ColorBuffer::GetHeight() const
{
	return m_height;
}

void ColorBuffer::SetPixelColor(size_t x, size_t y, const Color& color)
{
	m_data[x + y * m_width].r = color.r;
	m_data[x + y * m_width].g = color.g;
	m_data[x + y * m_width].b = color.b;
	m_data[x + y * m_width].a = color.a;
}

void ColorBuffer::Clear()
{
	std::memset(m_data, 0, GetSizeInBytes());
}
