#pragma once

#include <iostream>
#include <memory>

#include "controller/IController.h"
#include "view_model/Scene.h"
#include "view_model/SpaceObjectView.h"
#include "factory/SpaceObjectFactory.h"

class SetupController : public IController
{
public:
	SetupController(UniverseModel& model, Scene& viewModel, IControllableWindow* window);

private:
	// Inherited via IController
	virtual void OnIdle() override;
	virtual void OnMouseDown(const gfx::Vector& pos, int mods) override;
	virtual void OnMouseUp(const gfx::Vector& pos) override;
	virtual void OnMouseMove(const gfx::Vector& pos, const gfx::Vector& delta) override;
	virtual void OnKeyPress(int key) override;

	void InitSpaceObjects();

	SpaceObject* FindObjectAtPos(const gfx::Vector& pos);

	bool m_setupInitialSpeed, m_dragging;
	SpaceObject* m_activeObject;
	UniverseModel& m_model;
	Scene& m_scene;
	IControllableWindow* m_window;
};
