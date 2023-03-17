#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "glad_glfw.h"

#include "opengl_abstractions/Shader.h"

#include "view/Window.h"
#include "controller/SetupController.h"

static void GlfwErrorCalback(int error, const char* description);

int main()
{
	glfwSetErrorCallback(GlfwErrorCalback);
	if (!glfwInit())
		return 1;

	// GL 3.3 + GLSL 330
	const char* glsl_version = "#version 330";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Setup OpenGL core profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Enable multisampling
	glfwWindowHint(GLFW_SAMPLES, 4);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	int width = 600, height = 600;
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
