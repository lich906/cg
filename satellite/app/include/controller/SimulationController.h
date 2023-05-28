#pragma once

#include "AbstractController.h"

class SimulationController : public AbstractController
{
public:
	using AbstractController::AbstractController;

private:
	// Inherited via AbstractController
	virtual void OnIdle() override;
	virtual void OnMouseDown(const glm::vec2& pos, int mods) override;
	virtual void OnMouseUp(const glm::vec2& pos) override;
	virtual void OnMouseMove(const glm::vec2& pos, const glm::vec2& delta) override;
	virtual void OnKeyPress(int key) override;
	virtual void OnSet() override;
};
