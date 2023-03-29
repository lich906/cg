#pragma once

#include "IController.h"

class SimulationController : public IController
{
public:
	SimulationController(UniverseModel& model, Scene& scene, IControllableWindow* window);

private:
	// Inherited via IController
	virtual void OnDraw(int width, int height) override;
	virtual void OnMouseDown(const gfx::Vector& pos, int mods) override;
	virtual void OnMouseUp(const gfx::Vector& pos) override;
	virtual void OnMouseMove(const gfx::Vector& pos, const gfx::Vector& delta) override;
	virtual void OnKeyPress(int key) override;

	UniverseModel& m_model;
	Scene& m_scene;
	IControllableWindow* m_window;
};
