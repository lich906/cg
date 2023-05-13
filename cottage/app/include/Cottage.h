#pragma once

#include "AssimpMesh.h"
#include "Object.h"
#include "consts.h"

class Cottage : public Object
{
public:
	Cottage();

	virtual void OnDraw(gfx::Program& prog) override;

private:
	glm::mat4 m_transform;
	AssimpMesh m_mesh;
};
