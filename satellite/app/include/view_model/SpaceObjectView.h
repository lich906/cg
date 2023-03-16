#pragma once


#include <vector>

#include "types/Vertex.h"
#include "types/Vector.h"

#include "opengl_abstractions/Texture.h"
#include "opengl_abstractions/VertexArrayObjectWrapper.h"

#include "model/ISpaceObjectObserver.h"

class SpaceObjectView : public ISpaceObjectObserver
{
public:
	SpaceObjectView(const Vector& normalizedPos, float scale, Texture texture);

	void Draw(int width, int height);

	bool ExistsAtPos(const Vector& normalizedPos) const;

private:

	// Inherited via ISpaceObjectObserver
	virtual void OnSpaceObjectMove(const Vector& deltaPos) override;

	Vector m_deltaPos;

	float m_scale;

	Texture m_texture;

	std::vector<Vertex> m_vertices;

	VertexArrayObjectWrapper m_vaoWrapper;
};
