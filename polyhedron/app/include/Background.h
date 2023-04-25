#pragma once

#include "Object.h"

class Background : public Object
{
public:
	Background(const glm::vec4& color);

	virtual void OnDraw(gfx::Program& prog) override;

private:
	glm::vec4 m_color;
};
