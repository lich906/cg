#include "model/ImageObject.h"

ImageObject::ImageObject(int width, int height)
	: m_anchor({ 0.0f, 0.0f })
	, m_width(static_cast<float>(width))
	, m_height(static_cast<float>(height))
	, m_transform(1.0f)
{
	m_transform = glm::scale(glm::mat4(1.0f), glm::vec3(m_width, m_height, 1.0f));
}

bool ImageObject::ExistsAtPos(const gfx::Vector& pos)
{
	return m_anchor <= pos && pos <= m_anchor + gfx::Vector(m_width, m_height);
}

void ImageObject::Drag(const gfx::Vector& delta)
{
	if (delta)
	{
		m_anchor += delta;
		RefreshTransformMatrix();
	}
}

void ImageObject::ZoomIn()
{
	Zoom(config::ZoomingCoeff);
}

void ImageObject::ZoomOut()
{
	Zoom(-config::ZoomingCoeff);
}

glm::mat4 ImageObject::GetTransformMatrix()
{
	return m_transform;
}

void ImageObject::RefreshTransformMatrix()
{
	m_transform = glm::translate(glm::mat4(1.0f), glm::vec3(m_anchor.x, m_anchor.y, 0.0f));
	m_transform = glm::scale(m_transform, glm::vec3(m_width, m_height, 1.0f));
	TransformMatrixChanged();
}

void ImageObject::Zoom(float coeff)
{
	m_anchor -= gfx::Vector(coeff * m_width / 2, coeff * m_height / 2);
	m_width *= 1.0f + coeff;
	m_height *= 1.0f + coeff;
	RefreshTransformMatrix();
}
