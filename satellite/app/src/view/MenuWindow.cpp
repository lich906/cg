#include "view/MenuWindow.h"

#include "imgui.h"
#include "implot.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

MenuWindow::MenuWindow(IWindowContext* context)
	: m_context(context)
	, m_helpPopupOpen(false)
	, m_aboutPopupOpen(false)
{
	ImPlot::CreateContext();
	m_context->GetModel().RegisterObjectAddingObs([this](SpaceObject& obj) {
		RegisterVelocityPlots(obj);
	});
}

MenuWindow::~MenuWindow()
{
	ImPlot::DestroyContext();
}

void MenuWindow::Draw()
{
	if (ImGui::Begin("Main Menu", NULL, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse))
	{
		if (m_helpPopupOpen)
			ImGui::OpenPopup("Help");
		if (m_aboutPopupOpen)
			ImGui::OpenPopup("About");

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Help"))
			{
				if (ImGui::MenuItem("View Help"))
					m_helpPopupOpen = true;
				if (ImGui::MenuItem("About program"))
					m_aboutPopupOpen = true;
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
				m_helpPopupOpen = false;
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
				m_aboutPopupOpen = false;
			}
			ImGui::EndPopup();
		}

		ImGui::TextUnformatted("Positions:");

		m_context->GetModel().ForEach([&](const std::unique_ptr<SpaceObject>& object) -> void {
			ImGui::Text("%s: %.2f, %.2f", object->GetName().c_str(), object->GetCurrentPosition().x, object->GetCurrentPosition().y);
		});

		ImGui::Separator();

		if (ImGui::Button("Restart (Backspace)"))
			m_context->SetController(ControllerType::Setup);
		ImGui::SameLine();
		if (ImGui::Button("Exit"))
			m_context->CloseWindow();

		ImGui::TextUnformatted("Graphs: ");

		DrawVelocityPlots();

		ImGui::End();
	}
}

void MenuWindow::DrawVelocityPlots()
{
	if (!m_velocityPlots.empty())
	{
		m_t += config::Timestep;
		if (ImPlot::BeginPlot("Velocity", ImVec2(-1, 200)))
		{
			ImPlot::SetupAxes(NULL, NULL, ImPlotAxisFlags_NoTickLabels, ImPlotAxisFlags_NoTickLabels);
			ImPlot::SetupAxisLimits(ImAxis_X1, m_t - 30.0f, m_t, ImGuiCond_Always);
			ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 100.0f);
			ImPlot::SetNextFillStyle(IMPLOT_AUTO_COL, 0.5f);
			for (auto& [obj, plot] : m_velocityPlots)
			{
				plot->Draw(m_t);
			}
			ImPlot::EndPlot();
		}
	}
}

void MenuWindow::RegisterVelocityPlots(SpaceObject& object)
{
	m_velocityPlots[&object] = std::make_shared<SpaceObjectVelocityPlot>(object);

	m_connections += object.RegisterDeletionObs([this, ptr = &object]() {
		m_velocityPlots.erase(ptr);
		if (m_velocityPlots.empty())
			m_t = 0;
	});
}
