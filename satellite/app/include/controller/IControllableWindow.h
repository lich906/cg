#pragma once

#include <memory>

class WindowController;

struct IControllableWindow
{
	virtual ~IControllableWindow() = default;

	virtual void SetController(std::unique_ptr<WindowController>&& controller) = 0;
};
