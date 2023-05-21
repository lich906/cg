#include "ColorBuffer.h"

ColorBuffer::~ColorBuffer()
{
	Clear();
}

void ColorBuffer::Resize(uint32_t width, uint32_t height)
{
	m_width = width;
	m_height = height;
	delete[] m_data;
	m_data = new uint8_t[width * height * 4];
}

const uint8_t* ColorBuffer::GetData() const
{
	return m_data;
}

size_t ColorBuffer::GetSizeInBytes() const
{
	return m_width * m_height * sizeof(uint32_t);
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
	m_data[x * 4 + y * 4 * m_width    ] = color.r;
	m_data[x * 4 + y * 4 * m_width + 1] = color.g;
	m_data[x * 4 + y * 4 * m_width + 2] = color.b;
	m_data[x * 4 + y * 4 * m_width + 3] = color.a;
}

void ColorBuffer::Clear()
{
	memset(m_data, 0, GetSizeInBytes());
}
