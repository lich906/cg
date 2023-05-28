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

void SimulationController::OnMouseDown(const glm::vec2& pos, int mods)
{
}

void SimulationController::OnMouseUp(const glm::vec2& pos)
{
}

void SimulationController::OnMouseMove(const glm::vec2& pos, const glm::vec2& delta)
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
	GetContext()->GetModel().RegisterCollisionObs([this](const glm::vec2& v) {
		GetContext()->GetScene().AddNewObject(std::make_unique<Explosion>(v));
	});
}
