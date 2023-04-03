#pragma once

#include "implot.h"

#include "model/SpaceObject.h"
#include "ScrollingPlotBuffer.h"

class SpaceObjectVelocityPlot
{
public:
	SpaceObjectVelocityPlot(SpaceObject& obj);

	void Draw(float x);

private:
	float m_x;
	SpaceObject& m_object;
	ScrollingPlotBuffer m_buffer;
};
