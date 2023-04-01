#include "view/MenuWindow.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

MenuWindow::MenuWindow(UniverseModel& model)
	: m_model(model)
	, m_helpPopupOpen(false)
	, m_aboutPopupOpen(false)
{
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

		m_model.ForEach([&](const std::unique_ptr<SpaceObject>& object) -> void {
			ImGui::Text("%s: %.2f, %.2f", object->GetName().c_str(), object->GetCurrentPosition().x, object->GetCurrentPosition().y);
		});

		ImGui::Separator();

		ImGui::TextUnformatted("Graphs: ");
		ImGui::TextUnformatted("Soon...");

		ImGui::End();
	}
}
