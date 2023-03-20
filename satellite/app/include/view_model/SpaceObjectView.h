#pragma once

#include <memory>
#include <vector>

#include "types/Vertex.h"
#include "types/Vector.h"

#include "opengl_abstractions/Texture.h"
#include "opengl_abstractions/VertexArrayObject.h"

#include "model/ISpaceObjectObserver.h"

using SpaceObjectViewPtr = std::unique_ptr<class SpaceObjectView>;

class SpaceObjectView : public ISpaceObjectObserver
{
public:
	static SpaceObjectViewPtr Create(const Vector& position, float scale, Texture&& texture);

	void Draw(int width, int height);

	bool ExistsAtPos(const Vector& pos) const;

	void Move(const Vector& deltaPos);

private:

	SpaceObjectView(const Vector& pos, float scale, Texture&& texture);

	// Inherited via ISpaceObjectObserver
	virtual void OnSpaceObjectMove(const Vector& deltaPos) override;

	/*
		Update view position according accumulated m_deltaPos.
	*/
	void UpdatePosition(int width, int height);

	Vector m_deltaPos;

	Texture m_texture;

	std::vector<Vertex> m_vertices;

	VertexArrayObject m_vaoWrapper;
};
