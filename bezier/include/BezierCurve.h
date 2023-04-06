#pragma once

#include "graphics/Mesh.h"

class BezierCurve
{
public:
	BezierCurve(const gfx::Vector& p1, const gfx::Vector& p2, const gfx::Vector& p3, const gfx::Vector& p4);

	void Draw();

private:
	void InitMesh();
	std::vector<gfx::Vertex> GetCurveVertices();
	std::vector<GLuint> GetIndices(size_t size);
	std::optional<gfx::Mesh> m_mesh;
	gfx::Vector m_p1, m_p2, m_p3, m_p4;
};
