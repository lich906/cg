#pragma once

#include "SceneObject.h"
#include "graphics/Vector.h"
#include "graphics/Texture.h"
#include "graphics/Mesh.h"

class Arrow : public SceneObject
{
public:
	Arrow(const gfx::Vector& startP);

	void SetStartPoint(const gfx::Vector& p);
	void SetDirection(const gfx::Vector& p);

private:
	// Inherited via SceneObject
	virtual void DoDraw(int width, int height) override;

	void UpdateTransformation();

	gfx::Vector m_startPoint, m_direction;
	gfx::Texture m_texture;
	gfx::Mesh m_mesh;
};
