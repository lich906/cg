#pragma once

#include "ControllerType.h"
#include "model/UniverseModel.h"
#include "view_model/Scene.h"
#include "view/MenuWindow.h"

struct IWindowContext
{
	virtual ~IWindowContext() = default;

	virtual void SetController(ControllerType) = 0;
	virtual UniverseModel& GetModel() = 0;
	virtual Scene& GetScene() = 0;
	virtual MenuWindow& GetMenuWindow() = 0;
};
