#pragma once

#include <glm/glm.hpp>

#include "SceneObject.h"
#include "graphics/Texture.h"
#include "graphics/Mesh.h"

class Arrow : public SceneObject
{
public:
	Arrow(const glm::vec2& startP);

	void SetStartPoint(const glm::vec2& p);
	void SetDirection(const glm::vec2& p);

private:
	// Inherited via SceneObject
	virtual void DoDraw(int width, int height) override;

	void UpdateTransformation();

	glm::vec2 m_startPoint, m_direction;
	gfx::Texture m_texture;
	gfx::Mesh m_mesh;
};
