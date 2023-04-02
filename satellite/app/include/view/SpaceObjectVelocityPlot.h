#pragma once

#include "implot.h"

#include "model/SpaceObject.h"
#include "ScrollingPlotBuffer.h"

class SpaceObjectVelocityPlot
{
public:
	SpaceObjectVelocityPlot(SpaceObject& obj, const std::function<void()>& removeSelf);

	void Draw();

private:
	float m_x;
	SpaceObject& m_object;
	ScrollingPlotBuffer m_buffer;
	std::vector<ScopedConnection> m_connections;
	std::function<void()> m_removeSelf;
};
