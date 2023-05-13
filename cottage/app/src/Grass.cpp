#include "Grass.h"

Grass::Grass()
{
	if (!m_mesh.LoadMesh("assets/model/grass/grass.obj"))
	{
		throw std::runtime_error("Failed to load cottage model.");
	}
}

// Добавить фильтрацию текстур
void Grass::OnDraw(gfx::Program& prog)
{
	m_mesh.Draw();
}
