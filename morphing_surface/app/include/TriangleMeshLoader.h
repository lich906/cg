#pragma once

#include <array>
#include <string>

#include "graphics/Mesh.h"

class TriangleMeshLoader
{
public:
	static gfx::Mesh LoadFromFile(std::istream& input);
	static gfx::Mesh LoadFromFile(const std::string& fileName);

private:
	static std::array<glm::vec3, 3> ReadTriangleVertices(std::istream& input);
	static glm::vec4 ReadColor(std::istream& input);

};
