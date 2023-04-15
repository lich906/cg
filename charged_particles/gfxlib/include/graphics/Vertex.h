#pragma once

#include "pch.h"

#include "Vector.h"
#include "TexCoords.h"

namespace gfx
{

struct Vertex
{
	Vector position;
	TexCoords texCoords;
};

} // namespace gfx
