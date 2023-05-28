#include "HyperbolicParaboloid.h"

static constexpr float COEFF_A = 2.0f;
static constexpr float COEFF_B = 3.0f;

HyperbolicParaboloid::HyperbolicParaboloid(const glm::vec3& position)
	: m_mesh(GenerateVertices(), GenerateIndices())
	, m_transform(glm::translate(glm::mat4(1.0f), position))
{
}

void HyperbolicParaboloid::OnDraw(gfx::Program& prog)
{
	prog.SetUniformMatrix4fv("m_model", m_transform);

	GlCall(glEnable(GL_PRIMITIVE_RESTART));
	GlCall(glPrimitiveRestartIndex(consts::PRIMITIVE_RESTART_INDEX));
	GlCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));

	m_mesh.Draw(GL_TRIANGLE_STRIP);

	GlCall(glDisable(GL_PRIMITIVE_RESTART));
}

std::vector<gfx::Vertex> HyperbolicParaboloid::GenerateVertices() const
{
	std::vector<gfx::Vertex> vertices;

	for (float z = -consts::SURFACE_SIZE / 2; z <= consts::SURFACE_SIZE / 2; z += consts::SURFACE_QUAD_SIZE)
	{
		for (float x = -consts::SURFACE_SIZE / 2; x <= consts::SURFACE_SIZE / 2; x += consts::SURFACE_QUAD_SIZE)
		{
			float y = ((x * x) / (COEFF_A * COEFF_A) - (z * z) / (COEFF_B * COEFF_B)) / 2;
			gfx::Vertex::Position pos(x, y, z);
			vertices.emplace_back(gfx::Vertex{ pos, GetNormal(pos), consts::SURFACE_COLOR, {} });
		}
	}

	return vertices;
}

std::vector<GLuint> HyperbolicParaboloid::GenerateIndices() const
{
	std::vector<GLuint> indices;

	GLuint verticesPerRow = static_cast<GLuint>(consts::SURFACE_SIZE / consts::SURFACE_QUAD_SIZE) + 1;

	for (GLuint row = 0; row < verticesPerRow - 1; ++row)
	{
		for (GLuint col = 0; col < verticesPerRow; ++col)
		{
			indices.emplace_back(row * verticesPerRow + col);
			indices.emplace_back(row * verticesPerRow + col + verticesPerRow);
		}
		indices.emplace_back(consts::PRIMITIVE_RESTART_INDEX);
	}

	return indices;
}

gfx::Vertex::Normal HyperbolicParaboloid::GetNormal(const gfx::Vertex::Position& pos) const
{
	return -glm::normalize(glm::vec3((2 * pos.x) / (COEFF_A * COEFF_A), -1.0f, -(2 * pos.z) / (COEFF_B * COEFF_B)));
}
