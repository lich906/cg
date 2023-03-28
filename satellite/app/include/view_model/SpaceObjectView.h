#pragma once

#include <memory>
#include <vector>

#include "graphics/Vertex.h"
#include "graphics/Vector.h"
#include "graphics/Texture.h"

#include "model/ISpaceObjectObserver.h"
#include "view_model/SquareMesh.h"
#include "view_model/SceneObject.h"

class SpaceObjectView : public SceneObject, public ISpaceObjectObserver
{
public:
	static std::unique_ptr<SpaceObjectView> Create(const gfx::Vector& position, float scale, const gfx::Texture& texture);

private:
	SpaceObjectView(const gfx::Vector& pos, float scale, const gfx::Texture& texture);

	// Inherited via ISpaceObjectObserver
	virtual void OnSpaceObjectMove(const gfx::Vector& pos) override;
	virtual void OnVelocityChange(const gfx::Vector& value) override;

	// Inherited via SceneObject
	virtual void DoDraw(int width, int height) override;

	float m_scale;
	gfx::Texture m_texture;
	SquareMesh m_mesh;
};
