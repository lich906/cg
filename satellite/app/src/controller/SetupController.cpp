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

void SetupController::OnDraw(int width, int height)
{
	static bool show_demo_window = true;

	m_scene.Draw(width, height);
	ImGui::ShowDemoWindow(&show_demo_window);
	DrawMenuWindow();
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
	auto moon = SpaceObject::Create("Moon", config::MoonMass, config::MoonScale, config::MoonInitialPosition);
	auto moonView = SpaceObjectView::Create(
		config::MoonInitialPosition,
		config::MoonScale,
		gfx::Texture("res/textures/moon.png"));
	moon->Subsribe(moonView.get(), true);

	m_model.AddNewObject(std::move(moon));
	m_scene.AddNewObject(std::move(moonView));

	auto earth = SpaceObject::Create("Earth", config::EarthMass, config::EarthScale, config::EarthInitialPosition);
	auto earthView = SpaceObjectView::Create(
		config::EarthInitialPosition,
		config::EarthScale,
		gfx::Texture("res/textures/earth.png"));
	earth->Subsribe(earthView.get(), true);

	m_model.AddNewObject(std::move(earth));
	m_scene.AddNewObject(std::move(earthView));
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

		m_model.ForEach([&](const std::unique_ptr<SpaceObject>& object) -> void {
			ImGui::Text("%s: %.2f, %.2f", object->GetName().data(), object->GetCurrentPosition().x, object->GetCurrentPosition().y);
		});

		ImGui::Separator();

		ImGui::TextUnformatted("Graphs: ");

		ImGui::End();
	}
// clang-format on
}

SpaceObject* SetupController::FindObjectAtPos(const gfx::Vector& pos)
{
	return m_model.FindIf([&](const std::unique_ptr<SpaceObject>& obj) -> bool {
		return obj->ExistsAtPos(pos);
	});
}
