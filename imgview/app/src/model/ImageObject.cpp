#include "model/ImageObject.h"

ImageObject::ImageObject(int width, int height)
	: m_topLeft({ 0.0f, 0.0f })
	, m_bottomRight({ static_cast<float>(width), static_cast<float>(height) })
	, m_transform(1.0f)
{
	m_transform = glm::scale(m_transform, glm::vec3(m_bottomRight.x, m_bottomRight.y, 1.0f));
	//m_transform = glm::translate(m_transform, glm::vec3(m_topRight.x / 2, m_bottomLeft.y / 2, 0.0f));
}

bool ImageObject::ExistsAtPos(const Vector& pos)
{
	return m_topLeft <= pos && pos <= m_bottomRight;
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
