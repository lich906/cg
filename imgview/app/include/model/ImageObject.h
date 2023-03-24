#pragma once

#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp" // scale, translate
#include "graphics/Texture.h"
#include "graphics/Mesh.h"
#include "model/ObservableImageObject.h"

class ImageObject : public ObservableImageObject
{
public:
	ImageObject(int width, int height);

	bool ExistsAtPos(const Vector& pos);

	void Drag(const Vector& delta);

	void Zoom(float value);

private:
	// Inherited via ObservableImageObject
	virtual glm::mat4 GetTransformMatrix() override;

	Vector m_bottomLeft, m_topRight;
	glm::mat4 m_transform = glm::mat4(1.0f);
};
