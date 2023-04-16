#include "corepch.h"

#include "core/Application.h"
#include "core/GlfwWindow.h"
#include "core/event/EventDispatcher.h"

namespace core
{

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

Application* Application::s_instance = nullptr;

Application::Application(const std::string& name, uint32_t width, uint32_t height)
{
	s_instance = this;

	m_window = std::make_unique<GlfwWindow>(WindowProps{ name, width, height });
	m_conns += m_window->ListenEvents(BIND_EVENT_FN(OnEvent));
}

void Application::PushLayer(const std::shared_ptr<Layer>& layer)
{
	m_layerStack.PushLayer(layer);
}

void Application::PushOverlay(const std::shared_ptr<Layer>& layer)
{
	m_layerStack.PushOverlay(layer);
}

void Application::OnEvent(event::Event& e)
{
	event::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<event::WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

	for (auto it = m_layerStack.end(); it != m_layerStack.begin(); )
	{
		(*--it)->OnEvent(e);
		if (e.handled)
			break;
	}
}

void Application::Run()
{
	while (m_running)
	{
		float time = (float)glfwGetTime();
		Timestep timestep = time - m_lastFrameTime;
		m_lastFrameTime = time;

		for (const auto& layer : m_layerStack)
			layer->OnUpdate(timestep);

		m_window->OnUpdate();
	}
}

bool Application::OnWindowClose(event::WindowCloseEvent& e)
{
	m_running = false;
	return true;
}

} // namespace core
