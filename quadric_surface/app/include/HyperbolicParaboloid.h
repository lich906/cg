#pragma once

#include "consts.h"
#include "Object.h"
#include "graphics/Mesh.h"

class HyperbolicParaboloid : public Object
{
public:
	HyperbolicParaboloid(const glm::vec3& position);

	virtual void OnDraw(gfx::Program& prog) override;

private:
	std::vector<gfx::Vertex> GenerateVertices() const;
	std::vector<GLuint> GenerateIndices() const;
	gfx::Vertex::Normal GetNormal(const gfx::Vertex::Position& pos) const;

	gfx::Mesh m_mesh;
	glm::mat4 m_transform;
};
