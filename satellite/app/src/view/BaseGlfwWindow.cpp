#include "view/BaseGlfwWindow.h"

BaseGlfwWindow::BaseGlfwWindow(int width, int height, const char* title)
	: m_window(CreateGlfwWindow(width, height, title))
	, m_shader(InitGraphics())
{
	if (!m_window)
	{
		throw std::runtime_error("Failed to create window");
	}

	glfwSetWindowUserPointer(m_window, this);

	glfwSetKeyCallback(m_window, InvokeKeyCallback);
	glfwSetCursorPosCallback(m_window, InvokeCursorPosCallback);
	glfwSetMouseButtonCallback(m_window, InvokeMouseButtonCallback);
}

BaseGlfwWindow::~BaseGlfwWindow()
{
	glfwDestroyWindow(m_window);
}

void BaseGlfwWindow::Run()
{
	m_shader.Use();

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

Shader& BaseGlfwWindow::GetShaderRef()
{
	return m_shader;
}

void BaseGlfwWindow::SetupProjectionMatrix(int width, int height)
{
	// Вычисляет матрицу ортографического преобразования такую, чтобы вписать квадратную область
	// [-1;+1] по обеим осям внутрь видового порта размером width*height пикселей
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

Shader BaseGlfwWindow::InitGraphics()
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

	Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");
	shader.SetUniform1i("u_texture", 0); // Always use texture in 0 slot.
	return shader;
}

GLFWwindow* BaseGlfwWindow::CreateGlfwWindow(int width, int height, const char* title)
{
	return glfwCreateWindow(width, height, title, nullptr, nullptr);
}

void BaseGlfwWindow::InvokeKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	static_cast<BaseGlfwWindow*>(glfwGetWindowUserPointer(window))->m_keyCallback(window, key, scancode, action, mods);
}

void BaseGlfwWindow::InvokeCursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	static_cast<BaseGlfwWindow*>(glfwGetWindowUserPointer(window))->m_cursorPosCallback(window, xpos, ypos);
}

void BaseGlfwWindow::InvokeMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	static_cast<BaseGlfwWindow*>(glfwGetWindowUserPointer(window))->m_mouseButtonCallback(window, button, action, mods);
}
