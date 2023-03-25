#include "view/MainMenu.h"

MainMenu::MainMenu(const std::shared_ptr<IMenuController>& menuController)
	: m_controller(menuController)
	, m_errorModalOpen(false)
	, m_helpModalOpen(false)
{
}

void MainMenu::Draw()
{
	DrawMainMenuBar();
	DrawModals();
}

void MainMenu::DrawMainMenuBar()
{
	ImGui::BeginMainMenuBar();

	if (ImGui::MenuItem("Open File"))
		ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".png,.jpg,.jpeg,.bmp,.*", ".");

	if (ImGui::MenuItem("Close File"))
		m_controller->OnFileClose();

	if (ImGui::MenuItem("Help"))
		m_helpModalOpen = true;

	if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey"))
	{
		if (ImGuiFileDialog::Instance()->IsOk())
		{
			std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
			std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();

			try
			{
				m_controller->OnFileOpen(filePathName);
			}
			catch (std::runtime_error& e)
			{
				m_errorMsg = e.what();
				m_errorModalOpen = true;
			}
		}

		ImGuiFileDialog::Instance()->Close();
	}

	ImGui::EndMainMenuBar();
}

void MainMenu::DrawModals()
{
	if (m_errorModalOpen)
	{
		ImGui::OpenPopup("Error");
	}
	if (m_helpModalOpen)
	{
		ImGui::OpenPopup("Help");
	}

	if (ImGui::BeginPopupModal("Error", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("Error: %s\n", m_errorMsg.c_str());

		if (ImGui::Button("Close"))
		{
			ImGui::CloseCurrentPopup();
			m_errorModalOpen = false;
		}
		ImGui::EndPopup();
	}

	if (ImGui::BeginPopupModal("Help", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("Some help message that can explain\nhow to use this program.");

		if (ImGui::Button("Close"))
		{
			ImGui::CloseCurrentPopup();
			m_helpModalOpen = false;
		}
		ImGui::EndPopup();
	}
}
