#include "view_model/SquareMesh.h"

SquareMesh::SquareMesh()
	// clang-format off
		: Mesh(
		{{ { -0.5f, -0.5f }, { 0.0f, 1.0f } },
		 { { -0.5f, 0.5f }, { 0.0f, 0.0f } },
		 { { 0.5f, -0.5f }, { 1.0f, 1.0f } },
		 { { 0.5f, 0.5f }, { 1.0f, 0.0f } }},
		{ 0, 1, 2, 2, 1, 3 })
// clang-format on
{
}

void SquareMesh::Draw()
{
	Mesh::Draw();
}
