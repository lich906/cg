#include "SceneLayer.h"
#include "LightSource.h"
#include "Background.h"
#include "Polyhedron.h"
#include "Camera.h"

SceneLayer::SceneLayer()
	: m_program(gfx::Program("assets/shaders/lightning.vertex.glsl", "assets/shaders/lightning.fragment.glsl"))
{
}

void SceneLayer::OnAttach()
{
	m_program.Use();
	m_program.SetUniformMatrix4fv("m_model", glm::mat4(1.0f)); // Load identity matrices by default
	m_program.SetUniformMatrix4fv("m_view", glm::mat4(1.0f));

	core::IWindow& window = core::Application::Get().GetWindow();
	m_program.SetUniformMatrix4fv("m_projection",
		glm::perspective(
			glm::radians(45.0f),
			(float)window.GetWidth() / (float)window.GetHeight(),
			0.1f, 100.0f));

	std::unique_ptr<Object> bg = std::make_unique<Background>(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	std::unique_ptr<Object> camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, -4.0f));
	std::unique_ptr<Object> light = std::make_unique<LightSource>(
		glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	std::unique_ptr<Object> polyhedron = std::make_unique<Polyhedron>("mesh_data.txt", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	m_objects.emplace_back(std::move(bg));
	m_objects.emplace_back(std::move(camera));
	m_objects.emplace_back(std::move(light));
	m_objects.emplace_back(std::move(polyhedron));

	GlCall(glEnable(GL_DEPTH_TEST));
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
			m_program.SetUniformMatrix4fv("m_projection",
				glm::perspective(
					glm::radians(45.0f),
					(float)e.GetWidth() / (float)e.GetHeight(),
					0.1f, 100.0f));
			return false;
		});
}
