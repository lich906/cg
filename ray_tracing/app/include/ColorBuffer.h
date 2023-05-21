#pragma once

#include <vector>

#include "Color.h"

class ColorBuffer
{
public:
	ColorBuffer() = default;
	~ColorBuffer();

	void SetPixelColor(size_t x, size_t y, const Color& color);
	void Resize(uint32_t width, uint32_t height);
	void Clear();

	const uint8_t* GetData() const;
	size_t GetSizeInBytes() const;
	size_t GetWidth() const;
	size_t GetHeight() const;

private:
	uint8_t* m_data = nullptr;
	size_t m_width = 0, m_height = 0;
};
