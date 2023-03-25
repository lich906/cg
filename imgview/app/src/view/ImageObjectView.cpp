#include "view/ImageObjectView.h"

ImageObjectView::ImageObjectView(const Texture& texture)
	: m_transform(glm::mat4(1.0f))
	, m_backgroundTexture("res/textures/bg.png", GL_MIRRORED_REPEAT)
	, m_imageTexture(texture)
	// clang-format off
	, m_mesh(
		{{ { -1.0f,  1.0f },  { 0.0f, 1.0f } },
		 { { -1.0f, -1.0f },  { 0.0f, 1.0f } },
		 { {  1.0f,  1.0f },  { 0.0f, 1.0f } },
		 { {  1.0f, -1.0f },  { 0.0f, 1.0f } }},
		{ 0, 1, 2, 3 })
// clang-format on
{
}

void ImageObjectView::Draw()
{
	CurrentShader::Get().SetUniformMatrix4fv("m_model", m_transform);
	m_backgroundTexture.Bind();
	m_mesh.Draw(GL_TRIANGLE_STRIP);
	m_imageTexture.Bind();
	m_mesh.Draw(GL_TRIANGLE_STRIP);
}

void ImageObjectView::UpdateTransformMatrix(const glm::mat4& mat)
{
	m_transform = mat;
}
