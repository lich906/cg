#include "view/GraphicsInitializer.h"

GraphicsInitializer::GraphicsInitializer(int width, int height, const char* title)
{
	glfwSetErrorCallback([](int error, const char* description) -> void {
		printf("Glfw error #%d : %s\n", error, description);
	});

	if (!glfwInit())
		throw std::runtime_error("Failed to initialize GLFW.");

	// GL 3.3 + GLSL 330
	const char* glslVersion = "#version 330 core";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, config::graphics::GlfwContextVersionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, config::graphics::GlfwContextVersionMinor);
	// Setup OpenGL core profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Enable multisampling
	glfwWindowHint(GLFW_SAMPLES, config::graphics::GlfwSamples);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	// Create window with graphics context
	m_window = glfwCreateWindow(width, height, title, NULL, NULL);

	if (m_window == NULL)
		throw std::runtime_error("Failed to create GLFW window.");

	glfwMakeContextCurrent(m_window);
	gladLoadGL();
	glfwSwapInterval(1); // Enable vsync

	GlCall(glEnable(GL_BLEND));
	GlCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)); // Setup blending algorithm

#ifdef _DEBUG
	printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
#endif // _DEBUG
}

GraphicsInitializer::~GraphicsInitializer() noexcept
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

GLFWwindow* GraphicsInitializer::GetGLFWwindow() const
{
	return m_window;
}
