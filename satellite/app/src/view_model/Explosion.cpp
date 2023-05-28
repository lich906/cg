#include "view_model/Explosion.h"
#include "Config.h"

Explosion::Explosion(const glm::vec2& pos)
	: m_texture("res/textures/explosion.png")
	, m_timeElapsed(0.0f)
	, m_transMat(glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, 0.0f)))
{
	float scaleCoeff = config::ExplosionInitialScale;
	Transform(glm::scale(m_transMat, glm::vec3(scaleCoeff, scaleCoeff, 1.0f)));
}

void Explosion::DoDraw(int width, int height)
{
	gfx::CurrentProgram::Get().SetUniform1f("u_additionalAlpha", 1.0f - m_timeElapsed / config::ExplosionAnimationTime);
	m_texture.Bind();
	m_mesh.Draw();
	gfx::CurrentProgram::Get().SetUniform1f("u_additionalAlpha", 1.0f);
}

void Explosion::Update(float alpha)
{
	if ((m_timeElapsed += alpha) <= config::ExplosionAnimationTime)
	{
		float scaleCoeff = config::ExplosionInitialScale + m_timeElapsed * 20.0f;
		Transform(glm::scale(m_transMat, glm::vec3(scaleCoeff, scaleCoeff, 1.0f)));
	}
	else
	{
		RemoveSelf();
	}
}
