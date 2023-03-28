#pragma once

#include <memory>

class IController;

struct IControllableWindow
{
	virtual ~IControllableWindow() = default;

	virtual void SetController(std::unique_ptr<IController>&& controller) = 0;
};
