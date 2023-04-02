#pragma once

#include "AbstractController.h"

class NoObjectsLeftController : public AbstractController
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
};
