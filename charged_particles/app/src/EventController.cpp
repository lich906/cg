#include "EventController.h"
#include "PositiveParticleView.h"
#include "NegativeParticleView.h"
#include <GLFW/glfw3.h>

EventController::EventController(ParticlesModel& model, IParticlesLayer* layer)
	: m_model(model)
	, m_layer(layer)
	, m_camera(GLFW_MOUSE_BUTTON_MIDDLE)
{
	m_camera.SubscribeOnViewMatrixChange(std::bind(&EventController::OnViewMatrixChange, this, std::placeholders::_1));
}

void EventController::OnEvent(core::event::Event& event)
{
	m_camera.OnEvent(event);

	core::event::EventDispatcher dispatcher(event);

	DispatchMouseMove(dispatcher);
	DispatchMouseButtonPressed(dispatcher);
	DispatchKeyPressed(dispatcher);
}

void EventController::OnUpdate(core::Timestep timestep)
{
	m_model.OnUpdate(timestep);
}

void EventController::DispatchMouseMove(core::event::EventDispatcher& dispatcher)
{
	dispatcher.Dispatch<core::event::MouseMovedEvent>(
		[this](const core::event::MouseMovedEvent& e) {
			UpdateLastCursorPos(e.GetX(), e.GetY());
			return true;
		});
}

void EventController::DispatchMouseButtonPressed(core::event::EventDispatcher& dispatcher)
{
	dispatcher.Dispatch<core::event::MouseButtonPressedEvent>(
		[this](const core::event::MouseButtonPressedEvent& e) {
			int btnCode = e.GetMouseButton();
			if (btnCode == GLFW_MOUSE_BUTTON_LEFT || btnCode == GLFW_MOUSE_BUTTON_RIGHT)
			{
				if (!m_model.RemoveParticleAtPosIfExists(m_lastCursorPos))
					if (btnCode == GLFW_MOUSE_BUTTON_LEFT)
						AddPositiveParticle();
					else
						AddNegativeParticle();

				return true;
			}

			return false;
		});
}

void EventController::DispatchKeyPressed(core::event::EventDispatcher& dispatcher)
{
	dispatcher.Dispatch<core::event::KeyPressedEvent>(
		[this](const core::event::KeyPressedEvent& e) {
			switch (e.GetKeyCode())
			{
			case GLFW_KEY_DELETE:
				/*
					Remove particle views at this point is not necessarily
					since views remove themselfs if corresponding 'Particle' in model was removed.
					But I think that approach is more efficient.
				*/
				m_layer->RemoveAllParticleViews();
				m_model.RemoveAllParticles();
				return true;
			default:
				return false;
			}
		});
}

void EventController::AddPositiveParticle()
{
	auto particleView = std::make_unique<PositiveParticleView>(
		std::bind(&IParticlesLayer::RemoveParticleView, m_layer, std::placeholders::_1));
	auto particle = std::make_unique<Particle>(ParticleType::Positive, m_lastCursorPos);
	particleView->Observe(*particle);
	m_layer->AddParticleView(std::move(particleView));
	m_model.AddParticle(std::move(particle));
}

void EventController::AddNegativeParticle()
{
	auto particleView = std::make_unique<NegativeParticleView>(
		std::bind(&IParticlesLayer::RemoveParticleView, m_layer, std::placeholders::_1));
	auto particle = std::make_unique<Particle>(ParticleType::Negative, m_lastCursorPos);
	particleView->Observe(*particle);
	m_layer->AddParticleView(std::move(particleView));
	m_model.AddParticle(std::move(particle));
}

void EventController::UpdateLastCursorPos(float x, float y)
{
	m_camera.TransformScreenCoords(x, y);
	m_lastCursorPos.x = x;
	m_lastCursorPos.y = y;
}

void EventController::OnViewMatrixChange(const glm::mat4& vm)
{
	m_layer->GetProgram().SetUniformMatrix4fv("m_view", vm);
	GLFWwindow* wnd = (GLFWwindow*)core::Application::Get().GetWindow().GetNativeWindow();
	double x, y;
	glfwGetCursorPos(wnd, &x, &y);
	UpdateLastCursorPos((float)x, (float)y);
}
