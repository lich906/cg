#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include <memory>

#include "controller/IController.h"
#include "view_model/Scene.h"
#include "view_model/SpaceObjectView.h"

class SetupController : public IController
{
public:
	SetupController(UniverseModel& model, Scene& viewModel, IControllableWindow* window);

private:
	// Inherited via IController
	virtual void OnDraw(int width, int height) override;
	virtual void OnMouseDown(const gfx::Vector& pos, int mods) override;
	virtual void OnMouseUp(const gfx::Vector& pos) override;
	virtual void OnMouseMove(const gfx::Vector& pos, const gfx::Vector& delta) override;
	virtual void OnKeyPress(int key) override;

	void InitSpaceObjects();

	void DrawMenuWindow();

	SpaceObject* FindObjectAtPos(const gfx::Vector& pos);

	bool m_setupInitialSpeed, m_dragging;
	gfx::Vector m_mouseDownPos, m_dragOffset, m_prevCursorPos;
	SpaceObject* m_activeObject;
	UniverseModel& m_model;
	Scene& m_scene;
	IControllableWindow* m_window;
};
