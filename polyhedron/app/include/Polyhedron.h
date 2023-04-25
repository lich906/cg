#pragma once

#include "Object.h"
#include "graphics/Mesh.h"

class Polyhedron : public Object
{
public:
	Polyhedron(const std::string& fileName, const glm::vec4& color);

	virtual void OnDraw(gfx::Program& prog) override;

private:
	glm::mat4 m_transform;
	gfx::Mesh m_mesh;
};
