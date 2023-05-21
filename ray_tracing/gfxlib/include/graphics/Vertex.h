#pragma once

#include "gfxpch.h"

#include "TexCoords.h"

namespace gfx
{

struct Vertex
{
	using Position = glm::vec3;
	using Normal = glm::vec3;
	using TexCoords = glm::vec2;

	Position position;
	Normal normal;
	TexCoords texCoords;
};

} // namespace gfx
