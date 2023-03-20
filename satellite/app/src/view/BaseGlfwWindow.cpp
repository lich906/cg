#include "view/BaseGlfwWindow.h"
#include "opengl_abstractions/CurrentShader.h"

BaseGlfwWindow::BaseGlfwWindow(int width, int height, const char* title)
	: m_window(glfwCreateWindow(width, height, title, nullptr, nullptr))
{
	if (!m_window)
	{
		throw std::runtime_error("Failed to create window");
	}

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

	InitGraphics();
}

BaseGlfwWindow::~BaseGlfwWindow()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(m_window);
}

void BaseGlfwWindow::Run()
{


	while (!glfwWindowShouldClose(m_window))
	{
		glfwPollEvents();

		int width, height;
		glfwGetFramebufferSize(m_window, &width, &height);
		glViewport(0, 0, width, height);
		SetupProjectionMatrix(width, height);
		glClearColor(0.0f, 0.05f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Draw(width, height);

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

void BaseGlfwWindow::SetupProjectionMatrix(int width, int height)
{
	// ��������� ������� ���������������� �������������� �����, ����� ������� ���������� �������
	// [-1;+1] �� ����� ���� ������ �������� ����� �������� width*height ��������
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	const double aspectRatio = double(width) / double(height);
	double viewWidth = 2.0;
	double viewHeight = viewWidth;
	if (aspectRatio > 1.0)
	{
		viewWidth = viewHeight * aspectRatio;
	}
	else
	{
		viewHeight = viewWidth / aspectRatio;
	}
	glOrtho(-viewWidth * 0.5, viewWidth * 0.5, -viewHeight * 0.5, viewHeight * 0.5, -1.0, 1.0);
}

void BaseGlfwWindow::InitGraphics()
{
	glfwMakeContextCurrent(m_window);
	gladLoadGL();
	glfwSwapInterval(1); // Enable vsync

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init(config::graphics::GlslVersion);

	if constexpr (_DEBUG)
		printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

	CurrentShader::Set(Shader("shaders/vertex.glsl", "shaders/fragment.glsl"));
	CurrentShader::Get().SetUniform1i("u_texture", 0); // Always use texture in 0 slot.
	CurrentShader::Get().Use();
}
