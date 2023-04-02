#pragma once

#include "IWindowContext.h"

class AbstractController
{
public:
	AbstractController(IWindowContext* context);

	virtual ~AbstractController() = default;

	virtual void OnIdle() = 0;
	virtual void OnMouseDown(const gfx::Vector& pos, int mods) = 0;
	virtual void OnMouseUp(const gfx::Vector& pos) = 0;
	virtual void OnMouseMove(const gfx::Vector& pos, const gfx::Vector& delta) = 0;
	virtual void OnKeyPress(int key) = 0;
	virtual void OnSet() = 0;

protected:
	IWindowContext* GetContext();

private:
	IWindowContext* m_context;
};
