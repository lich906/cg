#include <cstring>
#include <stdexcept>

#include "ColorBuffer.h"

void ColorBuffer::Resize(uint32_t width, uint32_t height)
{
	m_data.resize(size_t(width * height));
	m_width = width;
	m_height = height;
}

const void* ColorBuffer::GetData() const
{
	return m_data.data();
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
	m_data.clear();
	m_data.resize(m_width * m_height);
}
