#pragma once

#include <iostream>

#include "WindowController.h"

class SetupController : public WindowController
{
public:
	SetupController(UniverseModel& model, UniverseViewModel& viewModel, IControllableWindow* window, int width, int height);

// Inherited via WindowController
	virtual void Draw(int width, int height) override;
	virtual GlfwMouseButtonCallback GetMouseButtonCallback() override;
	virtual GlfwCursorPosCallback GetCursorPosCallback() override;
	virtual GlfwKeyCallback GetKeyCallback() override;

private:

	void InitSpaceObjects(int width, int height);

	bool m_setupInitialSpeed, m_dragging;
	Vector m_mouseDownPos, m_dragOffset;
	size_t m_draggedObjectId;
};
