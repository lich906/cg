#pragma once

#include "graphics/Vector.h"
#include "graphics/CurrentProgram.h"

class Camera
{
public:

	static void OnCameraMove(const gfx::Vector& delta);
	static gfx::Vector GetOffset();
	static void UpdateViewMatrix();
	static void Reset();

private:

	static inline gfx::Vector m_offset;
};
