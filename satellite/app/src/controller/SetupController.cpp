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
		auto objectId = m_viewModel.FindObjectAtPos(NormalizeVector(mousePos, w, h));

		if (!m_dragging && action == GLFW_PRESS && objectId)
		{
			printf("Press\n");
			if (mods | GLFW_MOD_CONTROL)
			{
				m_setupInitialSpeed = true;
			}

			m_dragging = true;
			m_mouseDownPos = mousePos;
			m_draggedObjectId = *objectId;
			m_prevCursorPos = mousePos;
		}

		if (m_dragging && action == GLFW_RELEASE)
		{
			printf("\nRelease\n");
			m_setupInitialSpeed = false;
			m_dragging = false;
			m_model.MoveObject(m_draggedObjectId, m_dragOffset);
			m_dragOffset.x = m_dragOffset.y = 0.0f;
			m_prevCursorPos.x = m_prevCursorPos.y = 0.0f;
		}
	};
}

GlfwCursorPosCallback SetupController::GetCursorPosCallback()
{
	return [this](GLFWwindow* window, double xpos, double ypos) {
		if (m_dragging)
		{
			Vector cursorPos(xpos, ypos);
			Vector delta = cursorPos - m_prevCursorPos;
			m_viewModel.MoveObjectView(m_draggedObjectId, delta);
			m_dragOffset = cursorPos - m_mouseDownPos;

			printf("                                       \rDrag offset: %f.2\t%f.2\r", m_dragOffset.x, m_dragOffset.y);

			m_prevCursorPos = cursorPos;
		}
	};
}

GlfwKeyCallback SetupController::GetKeyCallback()
{
	return [this](GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (key == GLFW_KEY_ENTER && action == GLFW_RELEASE)
		{
			printf("ENTER released\n");
		}
	};
}

void SetupController::InitSpaceObjects(int width, int height)
{
	SpaceObjectPtr moon = std::make_unique<SpaceObject>(config::MoonMass, config::MoonInitialPosition);
	SpaceObjectViewPtr moonView = std::make_unique<SpaceObjectView>(NormalizeVector(config::MoonInitialPosition, width, height),
		config::MoonScale,
		Texture("res/textures/moon.png"));
	auto moonId = moon->GetId();
	moon->Subsribe(moonView.get());

	m_model.AddNewObject(std::move(moon));
	m_viewModel.AddNewObjectView(moonId, std::move(moonView));

	SpaceObjectPtr earth = std::make_unique<SpaceObject>(config::EarthMass, config::EarthInitialPosition);
	SpaceObjectViewPtr earthView = std::make_unique<SpaceObjectView>(NormalizeVector(config::EarthInitialPosition, width, height),
		config::EarthScale,
		Texture("res/textures/earth.png"));
	auto earthId = earth->GetId();
	earth->Subsribe(earthView.get());

	m_model.AddNewObject(std::move(earth));
	m_viewModel.AddNewObjectView(earthId, std::move(earthView));
}
