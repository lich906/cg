#pragma once

#include "core/core.h"
#include "graphics/Program.h"
#include "graphics/Mesh.h"
#include "Object.h"

class LightSource : public Object
{
public:
	LightSource(const glm::vec3& pos, const glm::vec4& color);

	virtual void OnEvent(core::event::Event& e) override;
	virtual void OnUpdate(core::Timestep ts) override;
	virtual void OnDraw(gfx::Program& prog) override;

private:
	glm::vec3 m_position;
	glm::vec4 m_lightColor;
	gfx::Mesh m_point;
	gfx::Program m_lightProgram;

	bool m_forward = false, m_backward = false,
		m_left = false, m_right = false,
		m_up = false, m_down = false;
};
