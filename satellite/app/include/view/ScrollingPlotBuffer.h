#pragma once

#include <vector>
#include <glm/glm.hpp>

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
	std::vector<glm::vec2> m_data;
};
