#include "view/Window.h"

Window::Window(const std::shared_ptr<Scene>& scene,
	const std::shared_ptr<IMouseInputController>& mouseInputController,
	const std::shared_ptr<IMenuController>& menuController)
	: m_clearColor{ 0.45f, 0.55f, 0.60f, 1.00f }
	, m_window(nullptr)
	, m_mainMenu(menuController)
	, m_mouseInputController(mouseInputController)
	, m_scene(scene)
{
	if (!InitGraphics())
	{
		throw std::runtime_error("Failed to initialize graphics.");
	}
}

Window::~Window()
{
	m_scene->RemoveImageObjectView();
	CurrentProgram::Unset();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void Window::Run()
{
	while (!glfwWindowShouldClose(m_window))
	{
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		UpdateProjectionMatrixAndViewport();
		Draw();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(m_window);
	}
}

void Window::Draw()
{
	GlCall(glClearColor(m_clearColor.r * m_clearColor.a, m_clearColor.g * m_clearColor.a, m_clearColor.b * m_clearColor.a, m_clearColor.a));
	GlCall(glClear(GL_COLOR_BUFFER_BIT));

	m_mainMenu.Draw();
	m_scene->Draw();
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

	GlCall(glEnable(GL_BLEND));
	GlCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)); // Setup blending algorithm

	if constexpr (_DEBUG)
		printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;

	SetupInputCallbacks();

	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	// ImGui::StyleColorsLight();
	Program program("shaders/vertex.glsl", "shaders/fragment.glsl");
	CurrentProgram::Set(program);
	CurrentProgram::Get().Use();
	CurrentProgram::Get().SetUniform1i("u_texture", 0); // Always use texture in 0 slot.
	CurrentProgram::Get().SetUniformMatrix4fv("m_model", glm::mat4(1.0f)); // Load identity matrices by default
	CurrentProgram::Get().SetUniformMatrix4fv("m_view", glm::mat4(1.0f));
	CurrentProgram::Get().SetUniformMatrix4fv("m_projection", glm::mat4(1.0f));

	return true;
}

void Window::SetupInputCallbacks()
{
	glfwSetWindowUserPointer(m_window, this);

	
	glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) -> void {
		auto thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		Vector cursorPos{ static_cast<float>(x), static_cast<float>(y) };

		if ((button == GLFW_MOUSE_BUTTON_LEFT || button == GLFW_MOUSE_BUTTON_RIGHT))
		{
			if (action == GLFW_PRESS)
			{
				thisWindow->m_mouseInputController->OnMouseDown(cursorPos);
			}
			if (action == GLFW_RELEASE)
			{
				thisWindow->m_mouseInputController->OnMouseUp(cursorPos);
			}
		}
	});

	glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos) -> void {
		auto thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
		Vector cursorPos{ static_cast<float>(xpos), static_cast<float>(ypos) };

		thisWindow->m_mouseInputController->OnMouseMove(cursorPos, cursorPos - thisWindow->m_lastCursorPos);
		thisWindow->m_lastCursorPos = cursorPos;
	});

	glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xoffset, double yoffset) -> void {
		auto thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		Vector cursorPos{ static_cast<float>(x), static_cast<float>(y) };

		if (yoffset > 0)
		{
			thisWindow->m_mouseInputController->OnScrollUp(cursorPos);
		}
		else
		{
			thisWindow->m_mouseInputController->OnScrollDown(cursorPos);
		}
	});
}

void Window::UpdateProjectionMatrixAndViewport()
{
	int w, h;
	glfwGetFramebufferSize(m_window, &w, &h);

	CurrentProgram::Get().SetUniformMatrix4fv("m_projection",
		glm::ortho(0.0f, float(w), float(h), 0.0f, -1.0f, 100.0f));

	GlCall(glViewport(0, 0, w, h));
}
