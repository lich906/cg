#include "PolyhedronLayer.h"

PolyhedronLayer::PolyhedronLayer()
	: m_program(gfx::Program("assets/shaders/lightning.vertex.glsl", "assets/shaders/lightning.fragment.glsl"))
{
}

void PolyhedronLayer::OnAttach()
{
	m_program.Use();
	m_program.SetUniformMatrix4fv("m_model", glm::mat4(1.0f)); // Load identity matrices by default
	m_program.SetUniformMatrix4fv("m_view", glm::mat4(1.0f));

	core::IWindow& window = core::Application::Get().GetWindow();
	m_program.SetUniformMatrix4fv("m_projection", 
		glm::perspective(
			glm::radians(45.0f),
			(float)window.GetWidth() / (float)window.GetHeight(),
			0.1f, 100.0f));

	LoadMesh();

	m_lightSource.SetLightColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	m_lightSource.SetPosition(glm::vec3(3.0f, 1.0f, -1.0f));
}

void PolyhedronLayer::OnDetach()
{
	m_mesh.reset();
}

void PolyhedronLayer::OnUpdate(core::Timestep ts)
{
	GlCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	GlCall(glClear(GL_COLOR_BUFFER_BIT));

	m_lightSource.Use(m_program);
	// Move polygon a bit forward from camera
	m_program.SetUniformMatrix4fv("m_model", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -4.0f)));

	m_mesh->Draw();
}

void PolyhedronLayer::LoadMesh()
{
	TriangleMeshLoader meshLoader({ 1.0f, 1.0f, 1.0f, 1.0f });
	std::ifstream inFile("mesh_data.txt");
	if (!inFile.is_open())
	{
		throw std::runtime_error("Failed to open mesh data file.");
	}
	m_mesh = meshLoader.LoadFormTxtFile(inFile);
}
