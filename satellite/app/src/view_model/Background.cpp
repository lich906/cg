#include "view_model/Background.h"

Background::Background()
	: m_texture("res/textures/sky.jpg")
{
}

void Background::DoDraw(int width, int height)
{
	static auto translate = glm::translate(glm::mat4(1.0f), glm::vec3(width / 2, height / 2, 0.0f));
	Transform(glm::scale(translate, glm::vec3(width, height, 1.0f)));
	m_texture.Bind();
	m_mesh.Draw();
}
