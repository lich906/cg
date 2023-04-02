#include "view/ScrollingPlotBuffer.h"

ScrollingPlotBuffer::ScrollingPlotBuffer()
	: m_maxSize(2000U)
	, m_offset(0)
{
	m_data.reserve(m_maxSize);
}

void ScrollingPlotBuffer::AddPoint(float x, float y)
{
	if (m_data.size() < m_maxSize)
	{
		m_data.push_back(gfx::Vector(x, y));
	}
	else
	{
		m_data[m_offset] = gfx::Vector(x, y);
		m_offset = (m_offset + 1) % int(m_maxSize);
	}
}

void ScrollingPlotBuffer::Erase()
{
	if (m_data.size() > 0)
	{
		m_data.resize(0);
		m_offset = 0;
	}
}

int ScrollingPlotBuffer::GetSize() const
{
	return m_data.size();
}

int ScrollingPlotBuffer::GetOffset() const
{
	return m_offset;
}

const float* ScrollingPlotBuffer::GetXData() const
{
	return &m_data[0].x;
}

const float* ScrollingPlotBuffer::GetYData() const
{
	return &m_data[0].y;
}
