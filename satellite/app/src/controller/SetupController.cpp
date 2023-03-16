#include "controller/SetupController.h"
#include "model/normalize_vector.h"
#include "model/Config.h"

SetupController::SetupController(UniverseModel& model, UniverseViewModel& viewModel, IControllableWindow* window, int width, int height)
	: WindowController(model, viewModel, window)
{
	m_model.RemoveAllObjects();
	m_viewModel.RemoveAllObjectViews();

	InitSpaceObjects(width, height);
}

void SetupController::Draw(int width, int height)
{
	m_viewModel.Draw(width, height);
}

GlfwMouseButtonCallback SetupController::GetMouseButtonCallback()
{
	return [this](GLFWwindow* window, int button, int action, int mods) {
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		int w, h;
		glfwGetFramebufferSize(window, &w, &h);
		Vector mousePos = { static_cast<float>(x), static_cast<float>(y) };
		auto norm = NormalizeVector(mousePos, w, h);
		std::cout << "Normalized v: " << norm.x << " " << norm.y << std::endl;
		auto objectId = m_viewModel.FindObjectAtPos(NormalizeVector(mousePos, w, h));
		std::cout << (objectId ? "Object here\n" : "Nothing\n");

		if (!m_dragging && action == GLFW_PRESS && objectId)
		{
			if (mods | GLFW_MOD_CONTROL)
			{
				m_setupInitialSpeed = true;
			}

			m_dragging = true;
			m_mouseDownPos = mousePos;
			m_draggedObjectId = *objectId;
		}

		if (m_dragging && action == GLFW_RELEASE)
		{
			m_setupInitialSpeed = false;
			m_dragging = false;
			m_dragOffset = { 0.0f, 0.0f };
		}
	};
}

GlfwCursorPosCallback SetupController::GetCursorPosCallback()
{
	return [this](GLFWwindow* window, double xpos, double ypos) {
		m_dragOffset.x = static_cast<float>(xpos) - m_mouseDownPos.x;
		m_dragOffset.y = static_cast<float>(ypos) - m_mouseDownPos.y;
	};
}

GlfwKeyCallback SetupController::GetKeyCallback()
{
	return GlfwKeyCallback();
}

void SetupController::InitSpaceObjects(int width, int height)
{
	SpaceObject moon(config::MoonMass, config::MoonInitialPosition, {});
	SpaceObjectView moonView(NormalizeVector(config::MoonInitialPosition, width, height),
		config::MoonScale,
		Texture("res/textures/moon.png"));
	auto moonId = moon.GetId();

	m_model.AddNewObject(std::move(moon));
	m_viewModel.AddNewObjectView(moonId, std::move(moonView));

	SpaceObject earth(config::EarthMass, config::EarthInitialPosition, {});
	SpaceObjectView earthView(NormalizeVector(config::EarthInitialPosition, width, height),
		config::EarthScale,
		Texture("res/textures/earth.png"));
	auto earthId = earth.GetId();

	m_model.AddNewObject(std::move(earth));
	m_viewModel.AddNewObjectView(earthId, std::move(earthView));
}
