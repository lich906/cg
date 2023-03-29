#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Config.h"
#include "view/Window.h"
#include "controller/SetupController.h"

int main()
{
	UniverseModel model;
	Scene viewModel;
	Window window(config::graphics::WindowWidth, config::graphics::WindowHeight, "Satellite");
	window.SetController(std::make_unique<SetupController>(model, viewModel, &window));
	window.Run();
}
