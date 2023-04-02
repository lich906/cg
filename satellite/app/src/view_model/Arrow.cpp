#include "view_model/Arrow.h"
#include "glm/gtx/vector_angle.hpp"
#include "Config.h"

Arrow::Arrow(const gfx::Vector& startP)
	: m_startPoint(startP)
	, m_direction(startP)
	, m_texture("res/textures/arrow.png")
// clang-format off
	, m_mesh(
		{
			{{ 0.0f, -0.5f }, { 0.0f, 1.0f }},
			{{ 0.0f, 0.5f }, { 0.0f, 0.0f }},
			{{ 1.0f, -0.5f }, { 1.0f, 1.0f }},
			{{ 1.0f, 0.5f }, { 1.0f, 0.0f }}
		},
		{0, 1, 2, 2, 1, 3})
// clang-format on
{
	Transform(glm::scale(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 1.0f)));
}

void Arrow::SetStartPoint(const gfx::Vector& p)
{
	m_startPoint = p;
	UpdateTransformation();
}

void Arrow::SetDirection(const gfx::Vector& p)
{
	m_direction = p;
	UpdateTransformation();
}

void Arrow::DoDraw(int width, int height)
{
	m_texture.Bind();
	m_mesh.Draw();
}

void Arrow::UpdateTransformation()
{
	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(m_startPoint.x, m_startPoint.y, 1.0f));
	float angle = glm::angle(glm::normalize(glm::vec3(m_direction.x, m_direction.y, 0.0f)), glm::vec3(1.0f, 0.0f, 0.0f));
	angle = m_direction.y < 0.0f ? -angle : angle;
	glm::mat4 rotate = glm::rotate(translate, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	float scaleCoeff = m_direction.Mod() * config::ArrowScaleCoeff;
	glm::mat4 scale = glm::scale(rotate, glm::vec3(scaleCoeff, scaleCoeff * 0.3f, 1.0f));
	Transform(scale);
}
