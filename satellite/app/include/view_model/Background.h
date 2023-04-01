#pragma once

#include "view_model/SceneObject.h"
#include "graphics/Texture.h"
#include "SquareMesh.h"

class Background : public SceneObject
{
public:
	Background();

private:

	// Inherited via SceneObject
	virtual void DoDraw(int width, int height) override;

	gfx::Texture m_texture;
	SquareMesh m_mesh;
};
