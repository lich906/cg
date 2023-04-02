#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Config.h"
#include "controller/SetupController.h"
#include "view/Window.h"
#include "view/GraphicsInitializer.h"

int main()
try
{
	GraphicsInitializer initializer(config::graphics::WindowWidth, config::graphics::WindowHeight, "Satellite");
	UniverseModel model;
	Scene scene;
	Window window(initializer.GetGLFWwindow(), model, scene);
	window.Run();
	//model.RemoveAllObjects();
}
catch (const std::runtime_error& e)
{
	std::cout << "Runtime error: " << e.what() << std::endl;
}
