#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "VertexArrayObjectWrapper.h"
#include "Shader.h"
#include "Texture.h"

static void glfw_error_callback(int error, const char* description);

int main()
{
	glfwSetErrorCallback(glfw_error_callback);
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

	// Create window with graphics context
	int width = 1280, height = 720;
	GLFWwindow* window = glfwCreateWindow(width, height, "Satellite", NULL, NULL);
	if (window == NULL)
		return 1;
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glfwSwapInterval(1); // Enable vsync

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;

	// ImGui::StyleColorsDark();
	ImGui::StyleColorsLight();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	{
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
		bool showDemoWindow = true;

		Vertex vertices[] = {
			// Position         Color                       Texture coords
			{ { -0.5f, 0.5f }, { 1.0f, 1.0f, 0.0f, 0.8f }, { 0.0f, 1.0f } },
			{ { -0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f, 0.8f }, { 0.0f, 0.0f } },
			{ { 0.5f, 0.5f }, { 0.0f, 1.0f, 0.0f, 0.8f }, { 1.0f, 1.0f } },
			{ { 0.5f, -0.5f }, { 0.0f, 0.0f, 1.0f, 0.8f }, { 1.0f, 0.0f } },
		};

		VertexArrayObjectWrapper triangle(sizeof(vertices), vertices, GL_STATIC_DRAW);
		Texture texture("res/textures/world_order.png");
		Shader shader("shaders/vertex.glsl", "shaders/fragment_texture_color_mesh.glsl");

		// Main loop
		while (!glfwWindowShouldClose(window))
		{
			glfwPollEvents();

			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			// ImGui::ShowDemoWindow(&showDemoWindow);

			// Rendering
			ImGui::Render();
			glViewport(0, 0, width, height);
			glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
			glClear(GL_COLOR_BUFFER_BIT);

			shader.Use();
			shader.SetUniform1i("u_texture", 0);
			texture.Bind(0);
			triangle.Draw(GL_TRIANGLE_STRIP);

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

static void glfw_error_callback(int error, const char* description)
{
	std::cout << "Glfw error " << error << ": " << description << std::endl;
}
