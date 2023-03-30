#include "view/BaseGlfwWindow.h"

BaseGlfwWindow::BaseGlfwWindow(int width, int height, const char* title)
{
	if (!InitGraphicsContext(width, height, title))
	{
		throw std::runtime_error("Failed to initialize graphics context.");
	}
}

BaseGlfwWindow::~BaseGlfwWindow()
{
	gfx::CurrentProgram::Unset();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void BaseGlfwWindow::Run()
{
	while (!glfwWindowShouldClose(m_window))
	{
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		UpdateProjectionMatrixAndViewport();

		glClearColor(config::graphics::ClearColor.r, config::graphics::ClearColor.g,
			config::graphics::ClearColor.b, config::graphics::ClearColor.a);
		glClear(GL_COLOR_BUFFER_BIT);
		Draw();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(m_window);
	}
}

void BaseGlfwWindow::SetKeyCallback(GlfwKeyCallback&& callback)
{
	m_keyCallback = std::move(callback);
}

void BaseGlfwWindow::SetCursorPosCallback(GlfwCursorPosCallback&& callback)
{
	m_cursorPosCallback = std::move(callback);
}

void BaseGlfwWindow::SetMouseButtonCallback(GlfwMouseButtonCallback&& callback)
{
	m_mouseButtonCallback = std::move(callback);
}

bool BaseGlfwWindow::InitGraphicsContext(int width, int height, const char* title)
{
	glfwSetErrorCallback([](int error, const char* description) -> void {
		printf("Glfw error #%d : %s\n", error, description);
	});

	if (!glfwInit())
		return false;

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
		return false;

	glfwMakeContextCurrent(m_window);
	gladLoadGL();
	glfwSwapInterval(1); // Enable vsync

	GlCall(glEnable(GL_BLEND));
	GlCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)); // Setup blending algorithm

#ifdef _DEBUG
	printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
#endif // _DEBUG

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;

	glfwSetWindowUserPointer(m_window, this);

	glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) -> void {
		static_cast<BaseGlfwWindow*>(glfwGetWindowUserPointer(window))->m_keyCallback(window, key, scancode, action, mods);
	});
	glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos) -> void {
		static_cast<BaseGlfwWindow*>(glfwGetWindowUserPointer(window))->m_cursorPosCallback(window, xpos, ypos);
	});
	glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) -> void {
		static_cast<BaseGlfwWindow*>(glfwGetWindowUserPointer(window))->m_mouseButtonCallback(window, button, action, mods);
	});

	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init(glslVersion);

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	// ImGui::StyleColorsLight();
	gfx::Program program("shaders/vertex.glsl", "shaders/fragment.glsl");
	gfx::CurrentProgram::Set(program);
	gfx::CurrentProgram::Get().Use();
	gfx::CurrentProgram::Get().SetUniform1i("u_texture", 0); // Always use texture in 0 slot.
	gfx::CurrentProgram::Get().SetUniformMatrix4fv("m_model", glm::mat4(1.0f)); // Load identity matrices by default
	gfx::CurrentProgram::Get().SetUniformMatrix4fv("m_view", glm::mat4(1.0f));
	gfx::CurrentProgram::Get().SetUniformMatrix4fv("m_projection", glm::mat4(1.0f));

	return true;
}

void BaseGlfwWindow::UpdateProjectionMatrixAndViewport()
{
	int w, h;
	glfwGetFramebufferSize(m_window, &w, &h);

	gfx::CurrentProgram::Get().SetUniformMatrix4fv("m_projection",
		glm::ortho(0.0f, float(w), float(h), 0.0f, -1.0f, 100.0f));

	GlCall(glViewport(0, 0, w, h));
}
