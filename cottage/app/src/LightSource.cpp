#include "LightSource.h"

constexpr float CONTROL_SPEED = 15.0f;

LightSource::LightSource(const glm::vec3& pos, const glm::vec4& color)
	: m_position(pos)
	, m_lightColor(color)
	, m_point({ gfx::Vertex{ pos, { 0.0f, 0.0f, 0.0f }, color } }, { 0 })
	, m_lightProgram("assets/shaders/light/vertex.glsl", "assets/shaders/light/fragment.glsl")
{
}

void LightSource::OnUpdate(core::Timestep ts)
{
	if (core::Input::IsKeyDown(core::KeyCode::W))
	{
		m_position.z -= ts * CONTROL_SPEED;
	}
	if (core::Input::IsKeyDown(core::KeyCode::S))
	{
		m_position.z += ts * CONTROL_SPEED;
	}
	if (core::Input::IsKeyDown(core::KeyCode::A))
	{
		m_position.x -= ts * CONTROL_SPEED;
	}
	if (core::Input::IsKeyDown(core::KeyCode::D))
	{
		m_position.x += ts * CONTROL_SPEED;
	}
	if (core::Input::IsKeyDown(core::KeyCode::Up))
	{
		m_position.y += ts * CONTROL_SPEED;
	}
	if (core::Input::IsKeyDown(core::KeyCode::Down))
	{
		m_position.y -= ts * CONTROL_SPEED;
	}
}

void LightSource::OnDraw(gfx::Program& prog)
{
	m_lightProgram.Use();
	m_lightProgram.SetUniformMatrix4fv("m_projection", prog.GetUniformContainer().Get<glm::mat4>("m_projection"));
	m_lightProgram.SetUniformMatrix4fv("m_view", prog.GetUniformContainer().Get<glm::mat4>("m_view"));
	m_lightProgram.SetUniformMatrix4fv("m_model", glm::translate(glm::mat4(1.0f), m_position));

	GlCall(glPointSize(10.0f));
	m_point.Draw(GL_POINTS);
	GlCall(glPointSize(1.0f));

	prog.Use();
	prog.SetUniform3fv("u_lightPosition", m_position);
	prog.SetUniform4fv("u_lightColor", m_lightColor);
}
