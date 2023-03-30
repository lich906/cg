#include "controller/SetupController.h"
#include "controller/SimulationController.h"
#include "Config.h"

SetupController::SetupController(UniverseModel& model, Scene& scene, IControllableWindow* window)
	: m_model(model)
	, m_scene(scene)
	, m_window(window)
{
	m_model.RemoveAllObjects();
	m_scene.RemoveAllObjects();

	InitSpaceObjects();
}

void SetupController::OnIdle()
{
}

void SetupController::OnMouseDown(const gfx::Vector& pos, int mods)
{
	if (!m_dragging && !m_setupInitialSpeed)
	{
		if (m_activeObject = FindObjectAtPos(pos))
		{
			if (mods & GLFW_MOD_CONTROL)
			{
				m_setupInitialSpeed = true;
			}
			else
			{
				m_dragging = true;
			}
		}
	}
}

void SetupController::OnMouseUp(const gfx::Vector& pos)
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

void SetupController::OnMouseMove(const gfx::Vector& pos, const gfx::Vector& delta)
{
	if (m_dragging || m_setupInitialSpeed)
	{
		gfx::Vector cursorPos(static_cast<float>(pos.x), static_cast<float>(pos.y));

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
		m_window->SetController(std::make_unique<SimulationController>(m_model, m_scene, m_window));
	}
}

void SetupController::InitSpaceObjects()
{
	auto moon = SpaceObjectFactory::CreateObjectAndView("Moon", config::MoonMass, config::MoonScale, gfx::Texture("res/textures/moon.png"), config::MoonInitialPosition);

	m_model.AddNewObject(std::move(moon.object));
	m_scene.AddNewObject(std::move(moon.view));

	auto earth = SpaceObjectFactory::CreateObjectAndView("Earth", config::EarthMass, config::EarthScale, gfx::Texture("res/textures/earth.png"), config::EarthInitialPosition);

	m_model.AddNewObject(std::move(earth.object));
	m_scene.AddNewObject(std::move(earth.view));
}

SpaceObject* SetupController::FindObjectAtPos(const gfx::Vector& pos)
{
	return m_model.FindIf([&](const std::unique_ptr<SpaceObject>& obj) -> bool {
		return obj->ExistsAtPos(pos);
	});
}
