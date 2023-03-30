#pragma once

#include "model/UniverseModel.h"
#include "view_model/Scene.h"
#include "IControllableWindow.h"
#include "GlfwCallbacks.h"

class IController
{
public:
	virtual ~IController() = default;

	virtual void OnIdle() = 0;
	virtual void OnMouseDown(const gfx::Vector& pos, int mods) = 0;
	virtual void OnMouseUp(const gfx::Vector& pos) = 0;
	virtual void OnMouseMove(const gfx::Vector& pos, const gfx::Vector& delta) = 0;
	virtual void OnKeyPress(int key) = 0;
};
