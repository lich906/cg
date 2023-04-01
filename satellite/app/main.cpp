#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Config.h"
#include "controller/SetupController.h"
#include "view/Window.h"
#include "view/GraphicsInitializer.h"

int main()
{
	GraphicsInitializer initializer(config::graphics::WindowWidth, config::graphics::WindowHeight, "Satellite");
	UniverseModel model;
	Scene scene;
	MenuWindow menuWindow(model);
	Window window(initializer.GetGLFWwindow(), scene, menuWindow);
	window.SetController(std::make_unique<SetupController>(model, scene, &window));
	window.Run();
}
