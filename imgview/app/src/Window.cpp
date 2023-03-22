#include "Window.h"

Window::Window(const std::shared_ptr<IMouseInputController>& mouseInputController,
	const std::shared_ptr<IMenuController>& menuController)
	: m_clearColor{ 0.45f, 0.55f, 0.60f, 1.00f }
	, m_window(nullptr)
	, m_mainMenu(menuController)
{
	if (!InitGraphics())
	{
		throw std::runtime_error("Failed to initialize graphics.");
	}
}

Window::~Window()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(m_window);
}

void Window::Run()
{
	while (!glfwWindowShouldClose(m_window))
	{
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		m_mainMenu.Render();
		Render();

		glfwSwapBuffers(m_window);
	}
}

void Window::Render()
{
	int w, h;
	glfwGetFramebufferSize(m_window, &w, &h);
	 
	CurrentShader::Get().SetUniformMatrix4fv("m_projection",
		glm::ortho(0.0f, float(w), float(h), 0.0f, -1.0f, 100.0f));

	glViewport(0, 0, w, h);

	glClearColor(m_clearColor.r * m_clearColor.a, m_clearColor.g * m_clearColor.a, m_clearColor.b * m_clearColor.a, m_clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool Window::InitGraphics()
{
	glfwSetErrorCallback([](int error, const char* description) -> void {
		printf("Glfw error #%d : %s\n", error, description);
	});

	if (!glfwInit())
		return false;

	// GL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Setup OpenGL core profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Enable multisampling
	glfwWindowHint(GLFW_SAMPLES, 4);

	// glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	// Create window with graphics context
	m_window = glfwCreateWindow(1280, 720, "Image Viewer", NULL, NULL);

	if (m_window == NULL)
		return false;

	glfwMakeContextCurrent(m_window);
	gladLoadGL();
	glfwSwapInterval(1); // Enable vsync

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Setup blending algorithm

	if constexpr (_DEBUG)
		printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;

	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	// ImGui::StyleColorsLight();

	CurrentShader::Set(Shader("shaders/vertex.glsl", "shaders/fragment.glsl"));
	CurrentShader::Get().SetUniform1i("u_texture", 0); // Always use texture in 0 slot.
	CurrentShader::Get().SetUniformMatrix4fv("m_model", glm::mat4(1.0f)); // Load identity matrices by default
	CurrentShader::Get().SetUniformMatrix4fv("m_view", glm::mat4(1.0f));

	CurrentShader::Get().Use();

	return true;
}
