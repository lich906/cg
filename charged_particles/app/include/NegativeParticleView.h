#pragma once

#include "graphics/Mesh.h"
#include "ParticleView.h"

class NegativeParticleView : public ParticleView
{
public:
	NegativeParticleView(const SelfRemovalFn& removeSelfFn);

private:
	// Inherited via ParticleView
	virtual void OnDrawImpl(const gfx::Program& program) const override;

	gfx::Mesh m_mesh;
};
