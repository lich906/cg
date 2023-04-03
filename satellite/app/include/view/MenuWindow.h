#pragma once

#include <vector>

#include "model/UniverseModel.h"
#include "ScrollingPlotBuffer.h"
#include "SpaceObjectVelocityPlot.h"

class MenuWindow
{
public:
	MenuWindow(UniverseModel& model);
	~MenuWindow();

	void Draw();

private:
	void DrawVelocityPlots();
	void RegisterVelocityPlots(SpaceObject& object);

	std::unordered_map<SpaceObject*, std::shared_ptr<SpaceObjectVelocityPlot>> m_velocityPlots;

	float m_t = 0.0f;
	bool m_helpPopupOpen, m_aboutPopupOpen;
	UniverseModel& m_model;
	std::vector<ScopedConnection> m_connections;
};
