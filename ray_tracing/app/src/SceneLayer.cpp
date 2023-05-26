#include "SceneLayer.h"
#include "Sphere.h"

#define BIND_EVENT_FN(x) std::bind(&SceneLayer::x, this, std::placeholders::_1)

SceneLayer::SceneLayer()
	: m_shader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl")
{
}

void SceneLayer::OnAttach()
{
	m_shader.Use();
	m_shader.SetUniform1i("u_texture", 0);

	Material sphereMaterial;
	sphereMaterial.Color = glm::vec3{ 1.0f, 0.5f, 0.0f };

	auto sphere = std::make_unique<Sphere>();
	sphere->SetMaterial(sphereMaterial);
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f));
	transform = glm::scale(transform, glm::vec3(2.0f, 1.0f, 1.0f));
	sphere->SetTransform(transform);

	m_scene.AddObject(std::move(sphere));

	core::IWindow& window = core::Application::Get().GetWindow();
	uint32_t width = (uint32_t)window.GetWidth(), height = (uint32_t)window.GetHeight();
	m_camera.OnResize(width, height);
	m_renderer.OnResize(width, height);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void SceneLayer::OnUpdate(core::Timestep ts)
{
	bool viewProjectionChanged = m_camera.OnUpdate(ts);

	if (viewProjectionChanged || m_firstFrame)
	{
		m_renderer.Render(m_scene, m_camera);
	}

	const ColorBuffer& colorBuffer = m_renderer.GetColorBuffer();

	glClear(GL_COLOR_BUFFER_BIT);
	glDrawPixels(
		(GLsizei)colorBuffer.GetWidth(),
		(GLsizei)colorBuffer.GetHeight(),
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		colorBuffer.GetData());

	if (m_firstFrame)
		m_firstFrame = false;
}

void SceneLayer::OnEvent(core::event::Event& event)
{
	core::event::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<core::event::WindowResizeEvent>(BIND_EVENT_FN(OnResize));
}

bool SceneLayer::OnResize(core::event::WindowResizeEvent& e)
{
	uint32_t width = e.GetWidth() ? e.GetWidth() : 1;
	uint32_t height = e.GetHeight() ? e.GetHeight() : 1;

	m_camera.OnResize(width, height);
	m_renderer.OnResize(width, height);
	m_renderer.Render(m_scene, m_camera);
	return true;
}
