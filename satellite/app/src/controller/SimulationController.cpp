#include "controller/SimulationController.h"
#include "controller/SetupController.h"
#include "view_model/Explosion.h"
#include <GLFW/glfw3.h>

void SimulationController::OnIdle()
{
	if (!GetContext()->GetModel().NextState(config::Timestep))
	{
		GetContext()->SetController(ControllerType::NoObjectsLeft);
	}
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
		GetContext()->SetController(ControllerType::Setup);
	}
}

void SimulationController::OnSet()
{
	GetContext()->GetModel().RegisterCollisionObs([this](const gfx::Vector& v) {
		GetContext()->GetScene().AddNewObject(std::make_unique<Explosion>(v));
	});
	GetContext()->GetScene().DispatchEvent(SceneEvent::HideArrows);
}
