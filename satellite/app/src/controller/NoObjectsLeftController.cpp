#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "controller/NoObjectsLeftController.h"

void NoObjectsLeftController::OnIdle()
{
	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.85f, 0.85f, 0.95f, 0.02f);
	ImGui::OpenPopup("GameOver");

	if (ImGui::BeginPopupModal("GameOver", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize))
	{
		ImGui::TextUnformatted("Simulation is over: No objects left.");
		ImGui::Separator();
		if (ImGui::Button("Restart")) GetContext()->SetController(ControllerType::Setup);
		ImGui::SameLine();
		if (ImGui::Button("Exit")) GetContext()->CloseWindow();

		ImGui::EndPopup();
	}
}

void NoObjectsLeftController::OnMouseDown(const gfx::Vector& pos, int mods)
{
}

void NoObjectsLeftController::OnMouseUp(const gfx::Vector& pos)
{
}

void NoObjectsLeftController::OnMouseMove(const gfx::Vector& pos, const gfx::Vector& delta)
{
}

void NoObjectsLeftController::OnKeyPress(int key)
{
}

void NoObjectsLeftController::OnSet()
{
}
