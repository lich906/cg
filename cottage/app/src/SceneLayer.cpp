#include "SceneLayer.h"
#include "LightSource.h"
#include "Background.h"
#include "Camera.h"
#include "Cottage.h"
#include "Grass.h"
#include "consts.h"

SceneLayer::SceneLayer()
	: m_lightProgram("assets/shaders/lightning.vertex.glsl", "assets/shaders/lightning.fragment.glsl")
{
}

void SceneLayer::OnAttach()
{
	m_lightProgram.Use();
	m_lightProgram.SetUniformMatrix4fv("m_model", glm::mat4(1.0f)); // Load identity matrices by default
	m_lightProgram.SetUniformMatrix4fv("m_view", glm::mat4(1.0f));
	m_lightProgram.SetUniform1i("u_texture", 0); // Always use texture in 0 slot.
	m_lightProgram.SetUniform1f("u_ambientValue", consts::AMBIENT_LIGHT_VALUE);

	core::IWindow& window = core::Application::Get().GetWindow();
	m_lightProgram.SetUniformMatrix4fv("m_projection",
		glm::perspective(
			glm::radians(45.0f),
			(float)window.GetWidth() / (float)window.GetHeight(),
			0.1f, 10000.0f));

	m_objects.emplace_back(std::make_unique<Background>(consts::BACKGROUND_COLOR));
	m_objects.emplace_back(std::make_unique<Camera>(consts::COTTAGE_POSITION));
	m_objects.emplace_back(std::make_unique<LightSource>(consts::LIGHT_SOURCE_INIT_POS, consts::LIGHT_COLOR));
	m_objects.emplace_back(std::make_unique<Cottage>());
	m_objects.emplace_back(std::make_unique<Grass>());

	GlCall(glEnable(GL_DEPTH_TEST));
	//GlCall(glEnable(GL_CULL_FACE));
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
		obj->OnDraw(m_lightProgram);
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
			m_lightProgram.Use();
			m_lightProgram.SetUniformMatrix4fv("m_projection",
				glm::perspective(
					glm::radians(45.0f),
					((float)e.GetWidth() + 1) / ((float)e.GetHeight() + 1),
					0.1f, 10000.0f));
			return false;
		});
}
