#pragma once

#include "gfxpch.h"

#include "TexCoords.h"

namespace gfx
{

struct Vertex
{
	using Position = glm::vec3;
	using Normal = glm::vec3;
	using Color = glm::vec4;

	Position position;
	Normal normal;
	Color color;
};

} // namespace gfx
