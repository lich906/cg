#pragma once

#include "AssimpMesh.h"
#include "Object.h"

class Grass : public Object
{
public:
	Grass();

	virtual void OnDraw(gfx::Program& prog) override;

private:
	AssimpMesh m_mesh;
};
