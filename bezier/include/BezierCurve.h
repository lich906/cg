#pragma once

#include "graphics/Mesh.h"

class BezierCurve
{
public:
	BezierCurve(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3, const glm::vec2& p4);

	void Draw();

private:
	void InitMesh();
	std::vector<gfx::Vertex> GetCurveVertices();
	std::vector<GLuint> GetIndices(size_t size);

	std::optional<gfx::Mesh> m_mesh;
	glm::vec2 m_p1, m_p2, m_p3, m_p4;
};
