#pragma once

#include <array>
#include <string>

#include "graphics/Mesh.h"

class TriangleMeshLoader
{
public:
	TriangleMeshLoader(gfx::Vertex::Color col);

	gfx::Mesh LoadFromFile(std::istream& input);
	gfx::Mesh LoadFromFile(const std::string& fileName);

private:

	std::array<glm::vec3, 3> ReadTriangleVertices(std::istream& input);

	gfx::Vertex::Color m_color;
};
