#include "ParticlesLayer.h"
#include "core/Application.h"

ParticlesLayer::ParticlesLayer(ParticlesModel& model)
	: m_controller(model, this)
	, m_program(gfx::Program("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl"))
{
}

void ParticlesLayer::OnAttach()
{
	m_program.Use();
	m_program.SetUniformMatrix4fv("m_model", glm::mat4(1.0f)); // Load identity matrices by default
	m_program.SetUniformMatrix4fv("m_view", glm::mat4(1.0f));

	core::IWindow& window = core::Application::Get().GetWindow();
	m_program.SetUniformMatrix4fv("m_projection", glm::ortho(
		0.0f, float(window.GetWidth()), float(window.GetHeight()), 0.0f, -1.0f, 1.0f));
}

void ParticlesLayer::OnUpdate(core::Timestep timestep)
{
	m_controller.OnUpdate(timestep);
	OnDraw();
}

void ParticlesLayer::OnEvent(core::event::Event& event)
{
	DispatchWindowResizeEvent(event);
	m_controller.OnEvent(event);
}

void ParticlesLayer::AddParticleView(std::unique_ptr<ParticleView>&& particleView)
{
	m_particleViews.emplace_back(std::move(particleView));
}

void ParticlesLayer::RemoveAllParticleViews()
{
	m_particleViews.clear();
}

void ParticlesLayer::RemoveParticleView(ParticleView* viewPtr)
{
	auto it = std::find_if(m_particleViews.begin(), m_particleViews.end(),
		[viewPtr](const std::unique_ptr<ParticleView>& particleView) {
			return particleView.get() == viewPtr;
		});

	if (it != m_particleViews.end())
		m_particleViews.erase(it);
}

void ParticlesLayer::OnDraw()
{
	for (auto& particleView : m_particleViews)
	{
		particleView->OnDraw(m_program);
	}
}

void ParticlesLayer::DispatchWindowResizeEvent(core::event::Event& event) const
{
	core::event::EventDispatcher dispatcher(event);

	dispatcher.Dispatch<core::event::WindowResizeEvent>(
		[this](core::event::WindowResizeEvent& e) {
			UpdateProjectionMatrixAndViewport((int)e.GetWidth(), (int)e.GetHeight());
			return true;
		});
}

void ParticlesLayer::UpdateProjectionMatrixAndViewport(int width, int height) const
{
	GlCall(glViewport(0, 0, width, height));
	//m_program.SetUniformMatrix4fv("m_projection", glm::ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f));
}

gfx::Program& ParticlesLayer::GetProgram()
{
	return m_program;
}
