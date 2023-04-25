#include "Polyhedron.h"
#include "TriangleMeshLoader.h"

Polyhedron::Polyhedron(const std::string& fileName, const glm::vec4& color)
	: m_mesh(TriangleMeshLoader(color).LoadFromFile(fileName))
	, m_transform(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -4.0f)))
{
}

void Polyhedron::OnDraw(gfx::Program& prog)
{
	prog.SetUniformMatrix4fv("m_model", m_transform);
	m_mesh.Draw();
}
