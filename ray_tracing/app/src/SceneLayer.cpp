#include <random>

#include "SceneLayer.h"
#include "Sphere.h"
#include "Plane.h"
#include "Torus.h"

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
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	transform = glm::scale(transform, glm::vec3(2.0f, 1.0f, 1.0f));
	sphere->SetTransform(transform);

	auto sphere2 = std::make_unique<Sphere>();
	sphere2->SetMaterial(Material(glm::vec3{ 0.1f, 0.7f, 0.2f }));
	transform = glm::translate(glm::mat4(1.0f), glm::vec3(2.5f, 2.0f, 5.0f));
	transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f));
	sphere2->SetTransform(transform);

	auto sphere3 = std::make_unique<Sphere>();
	sphere3->SetMaterial(Material(glm::vec3{ 0.1f, 0.7f, 1.0f }));
	transform = glm::translate(glm::mat4(1.0f), glm::vec3(2.5f, 1.0f, -1.0f));
	transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 0.5f));
	sphere3->SetTransform(transform);

	auto torus = std::make_unique<Torus>(1.0f, 0.5f);
	torus->SetMaterial(Material(glm::vec3{ 1.0f, 0.3f, 0.3f }));
	transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 3.0f));
	transform = glm::rotate(transform, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	torus->SetTransform(transform);

	auto plane = std::make_unique<Plane>(glm::vec3(0.0f, 1.0f, 0.0f));
	plane->SetMaterial(Material(glm::vec3{ 0.3f, 0.3f, 0.3f }));

	m_scene.AddObject(std::move(sphere));
	m_scene.AddObject(std::move(sphere2));
	m_scene.AddObject(std::move(sphere3));
	m_scene.AddObject(std::move(torus));
	m_scene.AddObject(std::move(plane));

	PointLight light;
	light.LightColor = glm::vec3(1.0f);

#if 1
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(-0.05f, 0.05f);
	const size_t pointLightsCount = 20;
	float totalIntensity = 1.0f;
	for (size_t i = 0; i < pointLightsCount; i++)
	{
		light.Intensity = (totalIntensity / pointLightsCount) + dist(gen);
		light.Position = glm::vec3(4.0f + dist(gen), 4.0f + dist(gen), 4.0f + dist(gen));
		m_scene.AddPointLight(light);
	}
#endif // 0
}
