#pragma once

#include "Particle.h"

class ParticleView
{
public:
	virtual ~ParticleView() = default;

	void Observe(Particle& particle);

	virtual void OnDraw() const = 0;

private:
	glm::mat4 m_transform;
};
