#pragma once

#include <memory>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "../vendor/ImGuiFileDialog/ImGuiFileDialog.h"

#include "IMenuController.h"

class MainMenu
{
public:
	MainMenu(const std::shared_ptr<IMenuController>& menuController);

	void Draw();

private:
	void DrawMainMenuBar();
	void DrawModals();

	std::shared_ptr<IMenuController> m_controller;

	bool m_helpModalOpen, m_errorModalOpen;
	std::string m_errorMsg;
};
