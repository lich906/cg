#include "view/MainMenu.h"

MainMenu::MainMenu(const std::shared_ptr<IMenuController>& menuController)
	: m_controller(menuController)
{
}

void MainMenu::Draw()
{
	ImGui::BeginMainMenuBar();

	if (ImGui::MenuItem("Open File"))
		ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".*", ".");

	if (ImGui::MenuItem("Close File"))
		m_controller->OnFileClose();

	ImGui::MenuItem("Help");

	if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey"))
	{
		if (ImGuiFileDialog::Instance()->IsOk())
		{
			std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
			std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
			// action
			m_controller->OnFileOpen(filePathName);
		}

		ImGuiFileDialog::Instance()->Close();
	}

	ImGui::EndMainMenuBar();
}
