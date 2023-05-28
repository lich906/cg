#pragma once

#include <memory>
#include <vector>
#include <array>
#include <glm/glm.hpp>

#include "graphics/Vertex.h"
#include "graphics/Texture.h"

#include "view_model/SquareMesh.h"
#include "view_model/SceneObject.h"
#include "view_model/Arrow.h"
#include "model/SpaceObject.h"
#include "signal/ScopedConnections.h"

class SpaceObjectView : public SceneObject
{
public:
	static std::unique_ptr<SpaceObjectView> Create(const glm::vec2& position, float scale, const gfx::Texture& texture);

	void Observe(SpaceObject& spaceObject);

private:
	SpaceObjectView(const glm::vec2& pos, float scale, const gfx::Texture& texture);

	void OnSpaceObjectMove(const glm::vec2& pos);
	void OnVelocityChange(const glm::vec2& v);

	// Inherited via SceneObject
	virtual void DoDraw(int width, int height) override;
	virtual void DispatchEvent(SceneEvent event) override;

	bool m_showArrow;
	float m_scale;
	gfx::Texture m_texture;
	SquareMesh m_mesh;
	Arrow m_arrow;

	ScopedConnections m_connections;
};
