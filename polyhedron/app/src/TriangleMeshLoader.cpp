#include "TriangleMeshLoader.h"

gfx::Mesh TriangleMeshLoader::LoadFromFile(std::istream& input)
{
	std::vector<gfx::Vertex> vertices;
	std::vector<GLuint> indices;

	while (input)
	{
		auto triangleVerts = ReadTriangleVertices(input);
		glm::vec3 normal = glm::cross(triangleVerts[1] - triangleVerts[0], triangleVerts[2] - triangleVerts[0]);
		normal = glm::normalize(normal);
		glm::vec4 color = ReadColor(input);

		vertices.push_back({ triangleVerts[0], normal, color });
		vertices.push_back({ triangleVerts[1], normal, color });
		vertices.push_back({ triangleVerts[2], normal, color });
		indices.push_back((GLuint)indices.size());
		indices.push_back((GLuint)indices.size());
		indices.push_back((GLuint)indices.size());
	}

	return gfx::Mesh(vertices, indices);
}

gfx::Mesh TriangleMeshLoader::LoadFromFile(const std::string& fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		throw std::runtime_error("Failed to open mesh data file.");
	}
	return LoadFromFile(file);
}

std::array<glm::vec3, 3> TriangleMeshLoader::ReadTriangleVertices(std::istream& input)
{
	std::array<glm::vec3, 3> vertices{ { {}, {}, {} } };

	for (size_t i = 0; i < 3 && input; ++i)
	{
		float x, y, z;
		input >> x >> y >> z;
		vertices[i] = glm::vec3(x, y, z);
	}

	return vertices;
}

glm::vec4 TriangleMeshLoader::ReadColor(std::istream& input)
{
	glm::vec4 col{};
	input >> col.r >> col.g >> col.b >> col.a;
	return col;
}
