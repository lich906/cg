
#include "GraphicsInitializer.h"
#include "graphics/CurrentProgram.h"
#include "BezierCurve.h"

constexpr int Width = 1280;
constexpr int Height = 720;

int main()
{
	GraphicsInitializer initializer(Width, Height, "Bezier curve");

	gfx::Program program("shaders/vertex.glsl", "shaders/fragment.glsl");
	gfx::CurrentProgram::Set(program);
	gfx::CurrentProgram::Get().Use();
	gfx::CurrentProgram::Get().SetUniformMatrix4fv("m_model", glm::mat4(1.0f)); // Load identity matrices by default
	gfx::CurrentProgram::Get().SetUniformMatrix4fv("m_view", glm::mat4(1.0f));
	gfx::CurrentProgram::Get().SetUniformMatrix4fv("m_projection",
		glm::ortho(0.0f, float(Width), float(Height), 0.0f, -1.0f, 100.0f));

	auto window = initializer.GetGLFWwindow();

	std::vector<gfx::Vector> points = {
		{ 200.0f, 500.0f },
		{ 300.0f, 200.0f },
		{ 500.0f, 250.0f },
		{ 700.0f, 500.0f }
	};

	BezierCurve bCurve(
		points[0],
		points[1],
		points[2],
		points[3]
	);

	gfx::Mesh pointsLine(
		{
			{ points[0], { 0.0f, 0.0f } },
			{ points[1], { 0.0f, 0.0f } },
			{ points[2], { 0.0f, 0.0f } },
			{ points[3], { 0.0f, 0.0f } },
		}, { 0, 1, 1, 2, 2, 3 });

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		gfx::CurrentProgram::Get().SetUniform4fv("u_color", glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
		pointsLine.Draw(GL_LINES);

		gfx::CurrentProgram::Get().SetUniform4fv("u_color", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		bCurve.Draw();

		glfwSwapBuffers(window);
	}

	gfx::CurrentProgram::Unset();

	return 0;
}
