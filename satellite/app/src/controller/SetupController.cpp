#include "controller/SetupController.h"
#include "controller/SimulationController.h"
#include "Config.h"

SetupController::SetupController(UniverseModel& model, UniverseViewModel& viewModel, IControllableWindow* window, int width, int height)
	: WindowController(model, viewModel, window)
{
	m_model.RemoveAllObjects();
	m_viewModel.RemoveAllObjectViews();

	InitSpaceObjects(width, height);
}

void SetupController::Draw(int width, int height)
{
	static bool show_demo_window = true;

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	m_viewModel.Draw(width, height);
	ImGui::ShowDemoWindow(&show_demo_window);
	DrawMenuWindow();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

GlfwMouseButtonCallback SetupController::GetMouseButtonCallback()
{
	return [this](GLFWwindow* window, int button, int action, int mods) {
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		Vector mousePos = { static_cast<float>(x), static_cast<float>(y) };
		auto objectId = m_viewModel.FindObjectAtPos(mousePos);

		if (!(m_draggingObject || m_setupInitialSpeed) && action == GLFW_PRESS && objectId)
		{
			if constexpr (_DEBUG) printf("Press\n");

			if (mods & GLFW_MOD_CONTROL)
			{
				m_setupInitialSpeed = true;
			}
			else
			{
				m_draggingObject = true;
			}

			m_mouseDownPos = mousePos;
			m_selectedObjectId = *objectId;
			m_prevCursorPos = mousePos;
		}

		if ((m_draggingObject || m_setupInitialSpeed) && action == GLFW_RELEASE)
		{
			if constexpr (_DEBUG) printf("\nRelease\n");

			auto& object = m_model.GetObject(m_selectedObjectId);

			if (m_draggingObject)
			{
				object->SetCurrentPosition(object->GetCurrentPosition() + m_dragOffset);
				m_draggingObject = false;
			}
			else
			{
				object->SetCurrentVelocity(object->GetCurrentVelocity() + m_dragOffset);
				m_setupInitialSpeed = false;
			}

			m_dragOffset.x = m_dragOffset.y = 0.0f;
			m_prevCursorPos.x = m_prevCursorPos.y = 0.0f;
		}
	};
}

GlfwCursorPosCallback SetupController::GetCursorPosCallback()
{
	return [this](GLFWwindow* window, double xpos, double ypos) {
		if (m_draggingObject || m_setupInitialSpeed)
		{
			Vector cursorPos(static_cast<float>(xpos), static_cast<float>(ypos));
			Vector delta = cursorPos - m_prevCursorPos;

			if (m_draggingObject)
			{
				m_viewModel.MoveObjectView(m_selectedObjectId, delta);
			}
			else
			{
				// update arrow view
			}

			if constexpr (_DEBUG) printf("                                       \rDrag offset: %f.2\t%f.2\r", m_dragOffset.x, m_dragOffset.y);
			m_dragOffset = cursorPos - m_mouseDownPos;
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
			m_window->SetController(std::make_unique<SimulationController>(m_model, m_viewModel, m_window));
		}
	};
}

void SetupController::InitSpaceObjects(int width, int height)
{
	SpaceObjectPtr moon = SpaceObject::Create("Moon", config::MoonMass, config::MoonInitialPosition);
	SpaceObjectViewPtr moonView = SpaceObjectView::Create(
		config::MoonInitialPosition,
		config::MoonScale,
		Texture("res/textures/moon.png"));
	auto moonId = moon->GetId();
	moon->Subsribe(moonView.get());

	m_model.AddNewObject(std::move(moon));
	m_viewModel.AddNewObjectView(moonId, std::move(moonView));

	SpaceObjectPtr earth = SpaceObject::Create("Earth", config::EarthMass, config::EarthInitialPosition);
	SpaceObjectViewPtr earthView = SpaceObjectView::Create(
		config::EarthInitialPosition,
		config::EarthScale,
		Texture("res/textures/earth.png"));
	auto earthId = earth->GetId();
	earth->Subsribe(earthView.get());

	m_model.AddNewObject(std::move(earth));
	m_viewModel.AddNewObjectView(earthId, std::move(earthView));
}

void SetupController::DrawMenuWindow()
{
// clang-format off
	if (ImGui::Begin("Main Menu", NULL, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse))
	{
		static bool helpPopupOpen = false;
		static bool aboutProgramPopupOpen = false;

		if (helpPopupOpen) ImGui::OpenPopup("Help");
		if (aboutProgramPopupOpen) ImGui::OpenPopup("About");

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Help"))
			{
				if (ImGui::MenuItem("View Help")) helpPopupOpen = true;
				if (ImGui::MenuItem("About program")) aboutProgramPopupOpen = true;
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		if (ImGui::BeginPopupModal("Help", NULL, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::Text("There will be help message soon.");

			if (ImGui::Button("Close"))
			{
				ImGui::CloseCurrentPopup();
				helpPopupOpen = false;
			}
			ImGui::EndPopup();
		}

		if (ImGui::BeginPopupModal("About", NULL, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::TextUnformatted("Moon and Earth simulation.");
			ImGui::Separator();
			ImGui::TextUnformatted("https://github.com/lich906");

			if (ImGui::Button("Close"))
			{
				ImGui::CloseCurrentPopup();
				aboutProgramPopupOpen = false;
			}
			ImGui::EndPopup();
		}

		ImGui::TextUnformatted("Positions:");

		m_model.ForEach([&](SpaceObjectPtr& object) -> void {
			ImGui::Text("%s: %.2f, %.2f", object->GetName().data(), object->GetCurrentPosition().x, object->GetCurrentPosition().y);
		});

		ImGui::Separator();

		ImGui::TextUnformatted("Graphs: ");

		ImGui::End();
	}
// clang-format on
}
