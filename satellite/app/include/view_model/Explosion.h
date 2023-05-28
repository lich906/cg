#pragma once

#include "SceneObject.h"
#include "SquareMesh.h"

class Explosion : public SceneObject
{
public:
	Explosion(const glm::vec2& position);

private:
	// Inherited via SceneObject
	virtual void DoDraw(int width, int height) override;
	virtual void Update(float alpha) override;

	SquareMesh m_mesh;
	gfx::Texture m_texture;
	glm::mat4 m_transMat;
	float m_timeElapsed;
};
