#pragma once

#include "model/UniverseModel.h"

class MenuWindow
{
public:
	MenuWindow(UniverseModel& model);

	void Draw();

private:
	bool m_helpPopupOpen, m_aboutPopupOpen;
	UniverseModel& m_model;
};
