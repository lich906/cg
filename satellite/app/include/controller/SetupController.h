#pragma once

#include <iostream>
#include <memory>

#include "controller/AbstractController.h"
#include "view_model/Scene.h"
#include "view_model/SpaceObjectView.h"
#include "factory/SpaceObjectFactory.h"

class SetupController : public AbstractController
{
public:
	using AbstractController::AbstractController;

private:
	// Inherited via AbstractController
	virtual void OnIdle() override;
	virtual void OnMouseDown(const gfx::Vector& pos, int mods) override;
	virtual void OnMouseUp(const gfx::Vector& pos) override;
	virtual void OnMouseMove(const gfx::Vector& pos, const gfx::Vector& delta) override;
	virtual void OnKeyPress(int key) override;
	virtual void OnSet() override;

	void InitSpaceObjects();

	SpaceObject* FindObjectAtPos(const gfx::Vector& pos);

	bool m_setupInitialSpeed, m_dragging;
	SpaceObject* m_activeObject;
};
