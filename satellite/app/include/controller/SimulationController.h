#pragma once

#include "WindowController.h"

class SimulationController : public WindowController
{
public:
	using WindowController::WindowController;

private:
	// Inherited via WindowController
	virtual void Draw(int width, int height) override;
	virtual GlfwMouseButtonCallback GetMouseButtonCallback() override;
	virtual GlfwCursorPosCallback GetCursorPosCallback() override;
	virtual GlfwKeyCallback GetKeyCallback() override;
};
