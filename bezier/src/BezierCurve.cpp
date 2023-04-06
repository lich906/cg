#include "BezierCurve.h"

BezierCurve::BezierCurve(const gfx::Vector& p1, const gfx::Vector& p2, const gfx::Vector& p3, const gfx::Vector& p4)
	: m_p1(p1)
	, m_p2(p2)
	, m_p3(p3)
	, m_p4(p4)
{
	InitMesh();
}

void BezierCurve::Draw()
{
	if (m_mesh)
	{
		m_mesh->Draw(GL_POINTS);
	}
}

void BezierCurve::InitMesh()
{
	auto vertices = GetCurveVertices();
	m_mesh = gfx::Mesh(vertices, GetIndices(vertices.size()));
}

std::vector<gfx::Vertex> BezierCurve::GetCurveVertices()
{
	// P = (1-t)^3*P1 + 3*(1-t)^2*t*P2 + 3*(1-t)*t^2*P3 + t^3*P4
	std::vector<gfx::Vertex> vertices;
	static float alpha = 0.0005f;

	for (float t = 0.0f; t < 1.0f; t += alpha)
	{
		gfx::Vertex v = {
			{ (1.0f - t) * (1.0f - t) * (1.0f - t) * m_p1.x + 3.0f * (1.0f - t) * (1.0f - t) * t * m_p2.x + 3.0f * (1 - t) * t * t * m_p3.x + t * t * t * m_p4.x,
				(1.0f - t) * (1.0f - t) * (1.0f - t) * m_p1.y + 3.0f * (1.0f - t) * (1.0f - t) * t * m_p2.y + 3.0f * (1 - t) * t * t * m_p3.y + t * t * t * m_p4.y
			},
			{ 0.0f, 0.0f }
		};
		vertices.emplace_back(std::move(v));
	}

	return vertices;
}

std::vector<GLuint> BezierCurve::GetIndices(size_t size)
{
	std::vector<GLuint> indices;
	for (size_t i = 0; i < size; ++i)
	{
		indices.push_back(i);
	}
	return indices;
}
