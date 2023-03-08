#include "GlfwInitializer.h"

GlfwInitializer::GlfwInitializer()
{
	if (!glfwInit())
	{
		throw std::runtime_error("Failed to initialize GLFW");
	}
}

GlfwInitializer::~GlfwInitializer()
{
	glfwTerminate();
}
