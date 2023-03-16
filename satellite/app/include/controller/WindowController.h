#pragma once

#include "model/UniverseModel.h"
#include "view_model/UniverseViewModel.h"
#include "IControllableWindow.h"
#include "GlfwCallbacks.h"

class WindowController
{
public:
	WindowController(UniverseModel& model, UniverseViewModel& viewModel, IControllableWindow* window);

	virtual void Draw(int width, int height) = 0;

	virtual GlfwMouseButtonCallback GetMouseButtonCallback() = 0;
	virtual GlfwCursorPosCallback GetCursorPosCallback() = 0;
	virtual GlfwKeyCallback GetKeyCallback() = 0;

protected:

	UniverseModel& m_model;

	UniverseViewModel& m_viewModel;

	IControllableWindow* m_window;
};
