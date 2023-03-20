#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "glad_glfw.h"

#include "Config.h"
#include "opengl_abstractions/Shader.h"
#include "view/Window.h"
#include "controller/SetupController.h"

static void GlfwErrorCalback(int error, const char* description);

int main()
{
	glfwSetErrorCallback(GlfwErrorCalback);
	if (!glfwInit())
		return 1;

	// GL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, config::graphics::GlfwContextVersionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, config::graphics::GlfwContextVersionMinor);
	// Setup OpenGL core profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Enable multisampling
	glfwWindowHint(GLFW_SAMPLES, config::graphics::GlfwSamples);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	 // ImGui::StyleColorsLight();

	int width = config::graphics::WindowWidth, height = config::graphics::WindowWidth;
	UniverseModel model;
	UniverseViewModel viewModel;
	Window window(width, height, "Satellite");
	window.SetController(std::make_unique<SetupController>(model, viewModel, &window, width, height));
	window.Run();

	glfwTerminate();
}

static void GlfwErrorCalback(int error, const char* description)
{
	std::cout << "Glfw error " << error << ": " << description << std::endl;
}
