#pragma once

#include "graphics/Mesh.h"

class TriangleMeshLoader
{
public:
	TriangleMeshLoader(gfx::Vertex::Color col);

	gfx::Mesh LoadFormTxtFile(std::istream& input);

private:

	gfx::Vector ReadVector(std::istream& input);

	gfx::Vertex::Color m_color;
};
