#pragma once

#include <memory>

#include "ParticleView.h"

class IParticlesLayer
{
public:
	virtual ~IParticlesLayer() = default;

	virtual void AddParticleView(std::unique_ptr<ParticleView>&& particleView) = 0;
	virtual void RemoveAllParticleViews() = 0;
	virtual void RemoveParticleView(ParticleView* viewPtr) = 0;
	virtual gfx::Program& GetProgram() = 0;
};
