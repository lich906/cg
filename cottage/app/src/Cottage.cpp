#include "Cottage.h"

Cottage::Cottage()
	: m_transform(glm::translate(glm::mat4(1.0f), consts::COTTAGE_POSITION))
{
	if (!m_mesh.LoadMesh("assets/model/cottage/House_01/House_01.obj"))
	{
		throw std::runtime_error("Failed to load cottage model.");
	}
}

void Cottage::OnDraw(gfx::Program& prog)
{
	prog.SetUniformMatrix4fv("m_model", m_transform);
	m_mesh.Draw();
}
