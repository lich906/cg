#include "SceneLayer.h"
#include "Background.h"
#include "RectangleMesh.h"

SceneLayer::SceneLayer()
	: m_program("assets/shaders/vertex.glsl", "assets/shaders/russia.fragment.glsl")
{
}

void SceneLayer::OnAttach()
{
	m_program.Use();
	m_program.SetUniformMatrix4fv("m_model", glm::mat4(1.0f)); // Load identity matrices by default
	m_program.SetUniformMatrix4fv("m_view", glm::lookAt(
		glm::vec3(0.0f, 0.0f, -4.0f), // camera pos
		glm::vec3(0.0f, 0.0f, 1.0f), // forward direction
		glm::vec3(0.0f, 1.0f, 0.0f)) // up direction
	);

	core::IWindow& window = core::Application::Get().GetWindow();
	m_program.SetUniformMatrix4fv("m_projection",
		glm::perspective(
			glm::radians(45.0f),
			(float)window.GetWidth() / (float)window.GetHeight(),
			0.1f, 100.0f));

	m_objects.emplace_back(std::make_unique<Background>(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)));
	m_objects.emplace_back(std::make_unique<RectangleMesh>());
}

void SceneLayer::OnDetach()
{
}

void SceneLayer::OnUpdate(core::Timestep ts)
{
	for (auto& obj : m_objects)
	{
		obj->OnUpdate(ts);
	}

	for (auto& obj : m_objects)
	{
		obj->OnDraw(m_program);
	}
}

void SceneLayer::OnEvent(core::event::Event& event)
{
	LayerOnEvent(event);

	for (auto& obj : m_objects)
	{
		obj->OnEvent(event);
	}
}

void SceneLayer::LayerOnEvent(core::event::Event& event)
{
	core::event::EventDispatcher dispatcher(event);

	dispatcher.Dispatch<core::event::WindowResizeEvent>(
		[this](core::event::WindowResizeEvent& e) {
			GlCall(glViewport(0, 0, e.GetWidth(), e.GetHeight()));
			m_program.Use();
			m_program.SetUniformMatrix4fv("m_projection",
				glm::perspective(
					glm::radians(45.0f),
					((float)e.GetWidth() + 1) / ((float)e.GetHeight() + 1),
					0.1f, 100.0f));
			return false;
		});
}
