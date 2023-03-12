#pragma once

#include "Vector.h"
#include "Color.h"
#include "TextureCoords.h"

struct Vertex
{
	Vector position;
	Color color;
	TextureCoords texCoords;
};
