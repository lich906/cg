#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include <memory>

#include "WindowController.h"

class SetupController : public WindowController
{
public:
	SetupController(UniverseModel& model, UniverseViewModel& viewModel, IControllableWindow* window, int width, int height);

private:
	// Inherited via WindowController
	virtual void Draw(int width, int height) override;
	virtual GlfwMouseButtonCallback GetMouseButtonCallback() override;
	virtual GlfwCursorPosCallback GetCursorPosCallback() override;
	virtual GlfwKeyCallback GetKeyCallback() override;

	void InitSpaceObjects(int width, int height);

	void DrawMenuWindow();

	bool m_setupInitialSpeed, m_draggingObject;
	Vector m_mouseDownPos, m_dragOffset, m_prevCursorPos;
	size_t m_selectedObjectId;
};
