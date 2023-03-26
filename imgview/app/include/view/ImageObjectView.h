#pragma once

#include "graphics/Texture.h"
#include "graphics/Mesh.h"
#include "graphics/CurrentProgram.h"
#include "model/IImageObjectObserver.h"

class ImageObjectView : public IImageObjectObserver
{
public:
	ImageObjectView(const Texture& texture);

	void Draw();

private:
	// Inherited via IImageObjectObserver
	void UpdateTransformMatrix(const glm::mat4&) override;

	Texture m_backgroundTexture, m_imageTexture;
	Mesh m_backgroundMesh;
	Mesh m_mesh;

	glm::mat4 m_transform;
};
