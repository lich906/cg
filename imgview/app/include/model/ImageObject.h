#pragma once

#include "config.h"
#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp" // scale, translate
#include "graphics/Texture.h"
#include "graphics/Mesh.h"
#include "model/ObservableImageObject.h"

class ImageObject : public ObservableImageObject
{
public:
	ImageObject(int width, int height);

	bool ExistsAtPos(const glm::vec2& pos);

	void Drag(const glm::vec2& delta);

	void ZoomIn();
	void ZoomOut();

private:
	// Inherited via ObservableImageObject
	virtual glm::mat4 GetTransformMatrix() override;

	void RefreshTransformMatrix();

	void Zoom(float coeff);

	glm::vec2 m_anchor;
	float m_width, m_height;
	glm::mat4 m_transform = glm::mat4(1.0f);
};
