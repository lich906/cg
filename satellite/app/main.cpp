#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "opengl_abstractions/VertexArrayObjectWrapper.h"
#include "opengl_abstractions/Shader.h"
#include "opengl_abstractions/Texture.h"

static void GlfwErrorCalback(int error, const char* description);

static void GlfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

static void SetupProjectionMatrix(int width, int height);

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

	//glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	// Create window with graphics context
	int width = 600, height = 600;
	GLFWwindow* window = glfwCreateWindow(width, height, "Satellite", NULL, NULL);
	if (window == NULL)
		return 1;
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glfwSwapInterval(1); // Enable vsync

	glfwSetMouseButtonCallback(window, GlfwMouseButtonCallback);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;

	// ImGui::StyleColorsDark();
	ImGui::StyleColorsLight();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	{
		ImVec4 clear_color = ImVec4(0.0f, 0.05f, 0.1f, 1.00f);
		bool showDemoWindow = true;

		VertexArrayObjectWrapper moon(
			{
				// Position         Color                       Texture coords
				{ { -0.05f, 0.05f }, { 1.0f, 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } },
				{ { -0.05f, -0.05f }, { 1.0f, 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
				{ { 0.05f, 0.05f }, { 0.0f, 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } },
				{ { 0.05f, -0.05f }, { 0.0f, 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } },
			},
			GL_STATIC_DRAW);

		VertexArrayObjectWrapper earth(
			{
				// Position         Color                       Texture coords
				{ { 0.35f, 0.45f }, { 1.0f, 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } },
				{ { 0.35f, 0.35f }, { 1.0f, 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
				{ { 0.45f, 0.45f }, { 0.0f, 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } },
				{ { 0.45f, 0.35f }, { 0.0f, 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } },
			},
			GL_STATIC_DRAW);

		Texture moonTexture("res/textures/moon.png");
		Texture earthTexture("res/textures/earth.png");
		Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");

		shader.SetUniform1i("u_texture", 0);

		// Main loop
		while (!glfwWindowShouldClose(window))
		{
			glfwPollEvents();

			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			//ImGui::ShowDemoWindow(&showDemoWindow);

			// Rendering
			ImGui::Render();
			glfwGetFramebufferSize(window, &width, &height);
			glViewport(0, 0, width, height);
			SetupProjectionMatrix(width, height);
			glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
			glClear(GL_COLOR_BUFFER_BIT);

			shader.Use();
			moonTexture.Bind(0);
			moon.Draw(GL_TRIANGLE_STRIP);
			earthTexture.Bind(0);
			earth.Draw(GL_TRIANGLE_STRIP);

			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(window);
		}
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}

static void GlfwErrorCalback(int error, const char* description)
{
	std::cout << "Glfw error " << error << ": " << description << std::endl;
}

void GlfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		int w, h;
		glfwGetFramebufferSize(window, &w, &h);
		std::cout << x << ' ' << y << "\t\t " << 2 * x / w - 1 << ' ' << 1 - 2 * y / h << std::endl;
	}
}

void SetupProjectionMatrix(int width, int height)
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
