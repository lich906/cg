#pragma once

#include <memory>

#include "ParticleView.h"

class IParticlesLayer
{
public:
	virtual ~IParticlesLayer() = default;

	virtual void AddParticleView(std::unique_ptr<ParticleView>&& particleView) = 0;
	virtual void RemoveAllParticleViews() = 0;
};
