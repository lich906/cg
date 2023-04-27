#include "Polyhedron.h"
#include "TriangleMeshLoader.h"
#include "consts.h"

Polyhedron::Polyhedron(const std::string& fileName, const glm::vec4& color)
	: m_mesh(TriangleMeshLoader(color).LoadFromFile(fileName))
	, m_transform(glm::translate(glm::mat4(1.0f), consts::POLYHEDRON_POSITION))
{
}

void Polyhedron::OnDraw(gfx::Program& prog)
{
	prog.SetUniformMatrix4fv("m_model", m_transform);
	GlCall(glEnable(GL_CULL_FACE));
	GlCall(glCullFace(GL_FRONT));
	m_mesh.Draw();
	GlCall(glCullFace(GL_BACK));
	m_mesh.Draw();
}
