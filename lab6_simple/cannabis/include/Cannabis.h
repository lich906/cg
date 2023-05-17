#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include "graphics/Mesh.h"
#include "Object.h"

constexpr float X_MIN = 0;
constexpr float X_MAX = float(2 * M_PI);
constexpr float X_STEP = float(M_PI / 1000);

class Cannabis : public Object
{
public:
	Cannabis();

private:
	virtual void OnDraw(gfx::Program& prog) override;

	static std::vector<gfx::Vertex> GenerateVertices();
	static std::vector<GLuint> GenerateIndices();

	gfx::Mesh m_mesh;
};
