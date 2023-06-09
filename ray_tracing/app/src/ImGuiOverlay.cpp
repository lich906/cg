#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "ImGuiOverlay.h"

ImGuiOverlay::ImGuiOverlay(Scene& scene)
	: Layer("ImGui Overlay")
	, m_scene(scene)
{
}

void ImGuiOverlay::OnAttach()
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	core::Application& app = core::Application::Get();
	GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
}

void ImGuiOverlay::OnDetach()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiOverlay::OnUpdate(core::Timestep)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	OnRender();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiOverlay::OnRender()
{
	static bool show = true;
	ImGui::ShowDemoWindow(&show);
}
