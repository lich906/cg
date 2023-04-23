#pragma once

#include "gfxpch.h"

#include "Vector.h"
#include "TexCoords.h"

namespace gfx
{

struct Vertex
{
	Vector position;
	struct Color
	{
		float r, g, b, a;
	} color;
	TexCoords texCoords;
};

} // namespace gfx
