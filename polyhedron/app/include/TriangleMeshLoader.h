#pragma once

#include <array>

#include "graphics/Mesh.h"

class TriangleMeshLoader
{
public:
	TriangleMeshLoader(gfx::Vertex::Color col);

	gfx::Mesh LoadFormTxtFile(std::istream& input);

private:

	std::array<glm::vec3, 3> ReadTriangleVertices(std::istream& input);

	gfx::Vertex::Color m_color;
};
