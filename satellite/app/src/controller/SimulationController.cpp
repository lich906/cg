#include "controller/SimulationController.h"
#include "controller/SetupController.h"

SimulationController::SimulationController(UniverseModel& model, Scene& scene, IControllableWindow* window)
	: m_model(model)
	, m_scene(scene)
	, m_window(window)
{
}

void SimulationController::OnIdle()
{
	m_model.NextState(config::Timestep);
}

void SimulationController::OnMouseDown(const gfx::Vector& pos, int mods)
{
}

void SimulationController::OnMouseUp(const gfx::Vector& pos)
{
}

void SimulationController::OnMouseMove(const gfx::Vector& pos, const gfx::Vector& delta)
{
}

void SimulationController::OnKeyPress(int key)
{
	if (key == GLFW_KEY_BACKSPACE)
	{
		m_window->SetController(std::make_unique<SetupController>(m_model, m_scene, m_window));
	}
}
