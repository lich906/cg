#include "SceneLayer.h"
#include "Sphere.h"
#include "Plane.h"

#define BIND_EVENT_FN(x) std::bind(&SceneLayer::x, this, std::placeholders::_1)

SceneLayer::SceneLayer()
	: m_shader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl")
{
}

void SceneLayer::OnAttach()
{
	m_shader.Use();
	m_shader.SetUniform1i("u_texture", 0);

	InitScene();

	core::IWindow& window = core::Application::Get().GetWindow();
	core::event::WindowResizeEvent resizeEvent(
		(uint32_t)window.GetWidth(),
		(uint32_t)window.GetHeight());
	OnResize(resizeEvent);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void SceneLayer::OnUpdate(core::Timestep ts)
{
	bool viewProjectionChanged = m_camera.OnUpdate(ts);

	if (viewProjectionChanged)
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

void SceneLayer::InitScene()
{
	auto sphere = std::make_unique<Sphere>();
	sphere->SetMaterial(Material(glm::vec3{ 1.0f, 0.5f, 0.0f }));
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	transform = glm::scale(transform, glm::vec3(2.0f, 1.0f, 1.0f));
	sphere->SetTransform(transform);

	auto plane = std::make_unique<Plane>(glm::vec3(1.0f, 1.0f, 0.0f));
	plane->SetMaterial(Material(glm::vec3{ 0.3f, 0.5f, 0.0f }));

	m_scene.AddObject(std::move(sphere));
	m_scene.AddObject(std::move(plane));
}
