#pragma once

#include <memory>
#include <vector>
#include <array>

#include "graphics/Vertex.h"
#include "graphics/Vector.h"
#include "graphics/Texture.h"

#include "view_model/SquareMesh.h"
#include "view_model/SceneObject.h"
#include "view_model/Arrow.h"
#include "model/SpaceObject.h"

class SpaceObjectView : public SceneObject
{
public:
	static std::unique_ptr<SpaceObjectView> Create(const gfx::Vector& position, float scale, const gfx::Texture& texture);

	void Observe(SpaceObject& spaceObject);

private:
	SpaceObjectView(const gfx::Vector& pos, float scale, const gfx::Texture& texture);

	void OnSpaceObjectMove(const gfx::Vector& pos);
	void OnVelocityChange(const gfx::Vector& v);

	// Inherited via SceneObject
	virtual void DoDraw(int width, int height) override;
	virtual void DispatchEvent(SceneEvent event) override;

	bool m_showArrow;
	float m_scale;
	gfx::Texture m_texture;
	SquareMesh m_mesh;
	Arrow m_arrow;

	std::vector<ScopedConnection> m_connections;
};
