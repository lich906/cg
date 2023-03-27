#pragma once

#include "graphics/Texture.h"
#include "graphics/Mesh.h"
#include "graphics/CurrentProgram.h"
#include "model/IImageObjectObserver.h"

class ImageObjectView : public IImageObjectObserver
{
public:
	ImageObjectView(const gfx::Texture& texture);

	void Draw();

private:
	// Inherited via IImageObjectObserver
	void UpdateTransformMatrix(const glm::mat4&) override;

	gfx::Texture m_backgroundTexture, m_imageTexture;
	gfx::Mesh m_backgroundMesh, m_mesh;

	glm::mat4 m_transform;
};
