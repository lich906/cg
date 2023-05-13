#include "LightSource.h"

constexpr float CONTROL_SPEED = 15.0f;

LightSource::LightSource(const glm::vec3& pos, const glm::vec4& color)
	: m_position(pos)
	, m_lightColor(color)
	, m_point({ gfx::Vertex{ pos, { 0.0f, 0.0f, 0.0f }, color } }, { 0 })
	, m_lightProgram("assets/shaders/light/vertex.glsl", "assets/shaders/light/fragment.glsl")
{
}

void LightSource::OnEvent(core::event::Event& event)
{
	core::event::EventDispatcher dispatcher(event);

	dispatcher.Dispatch<core::event::KeyPressedEvent>(
		[this](core::event::KeyPressedEvent& e) {
			switch (e.GetKeyCode())
			{
			case GLFW_KEY_W:
				m_backward = false;
				return m_forward = true;
			case GLFW_KEY_S:
				m_forward = false;
				return m_backward = true;
			case GLFW_KEY_A:
				m_right = false;
				return m_left = true;
			case GLFW_KEY_D:
				m_left = false;
				return m_right = true;
			case GLFW_KEY_UP:
				m_down = false;
				return m_up = true;
			case GLFW_KEY_DOWN:
				m_up = false;
				return m_down = true;
			default:
				return false;
			}
		});

	dispatcher.Dispatch<core::event::KeyReleasedEvent>(
		[this](core::event::KeyReleasedEvent& e) {
			switch (e.GetKeyCode())
			{
			case GLFW_KEY_W:
				m_forward = false;
				return true;
			case GLFW_KEY_S:
				m_backward = false;
				return true;
			case GLFW_KEY_A:
				m_left = false;
				return true;
			case GLFW_KEY_D:
				m_right = false;
				return true;
			case GLFW_KEY_UP:
				m_up = false;
				return true;
			case GLFW_KEY_DOWN:
				m_down = false;
			default:
				return true;
			}
		});
}

void LightSource::OnUpdate(core::Timestep ts)
{
	if (m_forward)
		m_position.z -= ts * CONTROL_SPEED;
	if (m_backward)
		m_position.z += ts * CONTROL_SPEED;
	if (m_left)
		m_position.x -= ts * CONTROL_SPEED;
	if (m_right)
		m_position.x += ts * CONTROL_SPEED;
	if (m_up)
		m_position.y += ts * CONTROL_SPEED;
	if (m_down)
		m_position.y -= ts * CONTROL_SPEED;
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
