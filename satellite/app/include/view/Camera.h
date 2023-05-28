#pragma once

#include <glm/glm.hpp>

#include "graphics/CurrentProgram.h"

class Camera
{
public:

	static void OnCameraMove(const glm::vec2& delta);
	static glm::vec2 GetOffset();
	static void UpdateViewMatrix();
	static void Reset();

private:

	static inline glm::vec2 m_offset;
};
