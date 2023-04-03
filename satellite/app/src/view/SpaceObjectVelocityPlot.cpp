#include "view/SpaceObjectVelocityPlot.h"

SpaceObjectVelocityPlot::SpaceObjectVelocityPlot(SpaceObject& obj)
	: m_x(0.0f)
	, m_object(obj)
{
}

void SpaceObjectVelocityPlot::Draw(float x)
{
	m_buffer.AddPoint(x, m_object.GetCurrentVelocity().Mod());
	ImPlot::PlotLine(m_object.GetName().c_str(), m_buffer.GetXData(), m_buffer.GetYData(), m_buffer.GetSize(), 0, m_buffer.GetOffset(), 2 * sizeof(float));
}
