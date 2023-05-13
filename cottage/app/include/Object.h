#pragma once

#include "core/core.h"
#include "graphics/Program.h"

class Object
{
public:
	virtual ~Object() = default;

	virtual void OnEvent(core::event::Event& e) {}
	virtual void OnUpdate(core::Timestep ts) {}
	// 
	virtual void OnDraw(gfx::Program& prog) {}
};
