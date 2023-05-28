#include "view/Camera.h"
#include "controller/SetupController.h"
#include "controller/SimulationController.h"
#include "Config.h"
#include "GLFW/glfw3.h"

void SetupController::OnIdle()
{
}

void SetupController::OnMouseDown(const glm::vec2& pos, int mods)
{
	if (!m_dragging && !m_setupInitialSpeed)
	{
		if (m_activeObject = FindObjectAtPos(pos))
		{
			if (mods & GLFW_MOD_CONTROL)
			{
				m_setupInitialSpeed = true;
				m_activeObject->SetCurrentVelocity({ 0.0f, 0.0f });
			}
			else
			{
				m_dragging = true;
			}
		}
	}
}

void SetupController::OnMouseUp(const glm::vec2& pos)
{
	if (m_dragging || m_setupInitialSpeed)
	{
		if (m_dragging)
		{
			m_dragging = false;
		}
		else
		{
			m_setupInitialSpeed = false;
		}
	}
}

void SetupController::OnMouseMove(const glm::vec2& pos, const glm::vec2& delta)
{
	if (m_dragging || m_setupInitialSpeed)
	{
		glm::vec2 cursorPos(static_cast<float>(pos.x), static_cast<float>(pos.y));

		if (m_dragging)
		{
			m_activeObject->SetCurrentPosition(m_activeObject->GetCurrentPosition() + delta);
		}
		else
		{
			m_activeObject->SetCurrentVelocity(m_activeObject->GetCurrentVelocity() + delta);
		}
	}
}

void SetupController::OnKeyPress(int key)
{
	if (key == GLFW_KEY_ENTER)
	{
		GetContext()->SetController(ControllerType::Simulation);
	}
}

void SetupController::OnSet()
{
	GetContext()->GetModel().RemoveAllObjects();

	InitSpaceObjects();

	Camera::Reset();
}

void SetupController::InitSpaceObjects()
{
	auto moon = SpaceObjectFactory::CreateObjectAndView("Moon", config::MoonMass, config::MoonScale, gfx::Texture("res/textures/moon.png"), config::MoonInitialPosition);

	GetContext()->GetModel().AddNewObject(std::move(moon.object));
	GetContext()->GetScene().AddNewObject(std::move(moon.view));

	auto earth = SpaceObjectFactory::CreateObjectAndView("Earth", config::EarthMass, config::EarthScale, gfx::Texture("res/textures/earth.png"), config::EarthInitialPosition);

	GetContext()->GetModel().AddNewObject(std::move(earth.object));
	GetContext()->GetScene().AddNewObject(std::move(earth.view));

	auto mars = SpaceObjectFactory::CreateObjectAndView("Mars", config::MarsMass, config::MarsScale, gfx::Texture("res/textures/mars.png"), config::MarsInitialPosition);

	GetContext()->GetModel().AddNewObject(std::move(mars.object));
	GetContext()->GetScene().AddNewObject(std::move(mars.view));
}

SpaceObject* SetupController::FindObjectAtPos(const glm::vec2& pos)
{
	return GetContext()->GetModel().FindIf([&](const std::unique_ptr<SpaceObject>& obj) -> bool {
		return obj->ExistsAtPos(pos);
	});
}
