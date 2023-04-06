#include "view_model/Background.h"
#include "view/Camera.h"

Background::Background()
	: m_texture("res/textures/sky.jpg")
{
}

void Background::DoDraw(int width, int height)
{
	auto cameraOffset = Camera::GetOffset();
	auto translate = glm::translate(glm::mat4(1.0f), glm::vec3(width / 2 - cameraOffset.x, height / 2 - cameraOffset.y, 0.0f));
	Transform(glm::scale(translate, glm::vec3(width, height, 1.0f)));
	m_texture.Bind();
	m_mesh.Draw();
}
