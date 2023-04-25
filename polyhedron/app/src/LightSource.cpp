#include "LightSource.h"

LightSource::LightSource(const glm::vec3& pos, const glm::vec4& color)
	: m_position(pos)
	, m_lightColor(color)
	, m_point({ gfx::Vertex{ { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } } }, { 0 })
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
	static const float speed = 0.5f;

	if (m_forward)
		m_position.z -= ts * speed;
	if (m_backward)
		m_position.z += ts * speed;
	if (m_left)
		m_position.x -= ts * speed;
	if (m_right)
		m_position.x += ts * speed;
	if (m_up)
		m_position.y += ts * speed;
	if (m_down)
		m_position.y -= ts * speed;
}

void LightSource::OnDraw(gfx::Program& prog)
{
	prog.SetUniform3fv("u_lightPosition", m_position);
	prog.SetUniform4fv("u_lightColor", m_lightColor);
	prog.SetUniform1f("u_ambientValue", 1.0f);

	prog.SetUniformMatrix4fv("m_model", glm::translate(glm::mat4(1.0f), m_position));
	GlCall(glPointSize(10.0f));
	m_point.Draw(GL_POINTS);

	prog.SetUniform1f("u_ambientValue", 0.1f);
}
