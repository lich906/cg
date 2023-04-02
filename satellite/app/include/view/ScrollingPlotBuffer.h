#pragma once

#include <vector>

#include "graphics/Vector.h"

class ScrollingPlotBuffer
{
public:
	ScrollingPlotBuffer();

	void AddPoint(float x, float y);
	void Erase();
	int GetSize() const;
	int GetOffset() const;
	const float* GetXData() const;
	const float* GetYData() const;

private:
	size_t m_maxSize;
	int m_offset;
	std::vector<gfx::Vector> m_data;
};
