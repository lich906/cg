#include "HyperbolicParaboloid.h"

static constexpr float MORPH_SPEED = 0.5f;
static constexpr float COEFF_A = 3.0f;
static constexpr float COEFF_B = 3.0f;

HyperbolicParaboloid::HyperbolicParaboloid(const glm::vec3& position)
	: m_mesh(GenerateVertices(), GenerateIndices())
	, m_transform(glm::translate(glm::mat4(1.0f), position))
{
}

void HyperbolicParaboloid::OnUpdate(core::Timestep ts)
{
	m_t = glm::cos(m_x += ts * MORPH_SPEED) * 0.5f + 0.5f;
}

void HyperbolicParaboloid::OnDraw(gfx::Program& prog)
{
	prog.SetUniformMatrix4fv("m_model", m_transform);
	prog.SetUniform3fv("u_normalMultiplier", GetNormalMultiplier());
	prog.SetUniform1f("u_t", m_t);
	prog.SetUniform1f("u_a_coeff", COEFF_A);
	prog.SetUniform1f("u_b_coeff", COEFF_B);

	GlCall(glEnable(GL_PRIMITIVE_RESTART));
	GlCall(glPrimitiveRestartIndex(consts::PRIMITIVE_RESTART_INDEX));
	GlCall(glPointSize(2.0f));
	GlCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));

	m_mesh.Draw(GL_TRIANGLE_STRIP);

	GlCall(glPointSize(1.0f));
	GlCall(glDisable(GL_PRIMITIVE_RESTART));
}

std::vector<gfx::Vertex> HyperbolicParaboloid::GenerateVertices() const
{
	std::vector<gfx::Vertex> vertices;

	for (float z = -consts::SURFACE_SIZE / 2; z <= consts::SURFACE_SIZE / 2; z += consts::SURFACE_QUAD_SIZE)
	{
		for (float x = -consts::SURFACE_SIZE / 2; x <= consts::SURFACE_SIZE / 2; x += consts::SURFACE_QUAD_SIZE)
		{
			gfx::Vertex::Position pos(x, 0.0f, z);
			vertices.emplace_back(gfx::Vertex{ pos, {}, consts::SURFACE_COLOR });
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

glm::vec3 HyperbolicParaboloid::GetNormalMultiplier() const
{
	return glm::vec3(2 / (COEFF_A * COEFF_A), 1.0f, 2 * (2 * m_t - 1) / (COEFF_B * COEFF_B));
}
