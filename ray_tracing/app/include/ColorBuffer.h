#pragma once

#include <vector>

#include "Color.h"

class ColorBuffer
{
public:
	void SetPixelColor(size_t x, size_t y, const Color& color);
	void Resize(uint32_t width, uint32_t height);
	void Clear();

	const void* GetData() const;
	size_t GetSizeInBytes() const;
	size_t GetWidth() const;
	size_t GetHeight() const;

private:
	//переделать с использованием std::vector
	std::vector<Color> m_data;
	size_t m_width = 0, m_height = 0;
};
