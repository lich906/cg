#include "model/ImageObject.h"

ImageObject::ImageObject(int width, int height)
	: m_bottomLeft({ 0.0f, static_cast<float>(height) })
	, m_topRight({ static_cast<float>(width), 0.0f })
	, m_transform(glm::mat4(1.0f))
// clang-format on
{
	m_transform = glm::translate(m_transform, glm::vec3(m_topRight.x / 2, m_bottomLeft.y / 2, 0.0f));
	m_transform = glm::scale(m_transform, glm::vec3(m_topRight.x, m_topRight.y, 0.0f));
}

bool ImageObject::ExistsAtPos(const Vector& pos)
{
	return m_bottomLeft <= pos && pos <= m_topRight;
}

void ImageObject::Drag(const Vector& delta)
{
	m_transform = glm::translate(m_transform, glm::vec3(delta.x, delta.y, 0.0f));
}

void ImageObject::Zoom(float value)
{
	value *= 1.1f;
	m_transform = glm::scale(m_transform, glm::vec3(value, value, 0.0f));
}

glm::mat4 ImageObject::GetTransformMatrix()
{
	return m_transform;
}
