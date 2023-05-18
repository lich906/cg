#pragma once

#include "consts.h"
#include "Object.h"
#include "graphics/Mesh.h"

class HyperbolicParaboloid : public Object
{
public:
	HyperbolicParaboloid(const glm::vec3& position);

private:
	virtual void OnUpdate(core::Timestep ts) override;
	virtual void OnDraw(gfx::Program& prog) override;

	std::vector<gfx::Vertex> GenerateVertices() const;
	std::vector<GLuint> GenerateIndices() const;
	glm::vec3 GetNormalMultiplier() const;

	gfx::Mesh m_mesh;
	glm::mat4 m_transform;
	float m_t = 0.0f, m_x = 0.0f;
};
