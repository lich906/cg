#include "TriangleMeshLoader.h"

TriangleMeshLoader::TriangleMeshLoader(gfx::Vertex::Color col)
	: m_color(col)
{
}

gfx::Mesh TriangleMeshLoader::LoadFormTxtFile(std::istream& input)
{
	std::vector<gfx::Vertex> vertices;
	std::vector<GLuint> indices;

	while (input)
	{
		gfx::Vector pos = ReadVector(input);
		vertices.push_back({ pos, m_color, { 0.0f, 0.0f } });
		indices.push_back(indices.size());
	}

	return gfx::Mesh(vertices, indices);
}

gfx::Vector TriangleMeshLoader::ReadVector(std::istream& input)
{
	float x, y, z;
	input >> x >> y >> z;
	return { x, y, z };
}
