#pragma once

#include "IWindowContext.h"

class AbstractController
{
public:
	AbstractController(IWindowContext* context);

	virtual ~AbstractController() = default;

	virtual void OnIdle() = 0;
	virtual void OnMouseDown(const glm::vec2& pos, int mods) = 0;
	virtual void OnMouseUp(const glm::vec2& pos) = 0;
	virtual void OnMouseMove(const glm::vec2& pos, const glm::vec2& delta) = 0;
	virtual void OnKeyPress(int key) = 0;
	virtual void OnSet() = 0;

protected:
	IWindowContext* GetContext();

private:
	IWindowContext* m_context;
};
