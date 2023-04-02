#include "view/SpaceObjectVelocityPlot.h"

SpaceObjectVelocityPlot::SpaceObjectVelocityPlot(SpaceObject& obj, const std::function<void()>& removeSelf)
	: m_x(0.0f)
	, m_object(obj)
	, m_removeSelf(removeSelf)
{
	m_connections.push_back(obj.RegisterDeletionObs([&]() {
		m_buffer.Erase();
		m_removeSelf();
	}));
}

void SpaceObjectVelocityPlot::Draw()
{
	m_x += ImGui::GetIO().DeltaTime;
	m_buffer.AddPoint(m_x, m_object.GetCurrentVelocity().Mod());
	ImPlot::PlotLine(m_object.GetName().c_str(), m_buffer.GetXData(), m_buffer.GetYData(), m_buffer.GetSize(), 0, m_buffer.GetOffset(), 2 * sizeof(float));
}
