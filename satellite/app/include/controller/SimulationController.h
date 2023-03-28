#pragma once

#include "IController.h"

class SimulationController : public IController
{
public:
	using IController::IController;

private:
	// Inherited via WindowController
	virtual void Draw(int width, int height) override;
	virtual GlfwMouseButtonCallback GetMouseButtonCallback() override;
	virtual GlfwCursorPosCallback GetCursorPosCallback() override;
	virtual GlfwKeyCallback GetKeyCallback() override;
};
