#pragma once

#include "consts.h"
#include "Particle.h"
#include "graphics/Program.h"
#include "core/utils/ScopedConnections.h"

class ParticleView
{
public:
	using SelfRemovalFn = std::function<void(ParticleView*)>;

	virtual ~ParticleView() = default;

	void Observe(Particle& particle);
	void OnDraw(const gfx::Program& program) const;

protected:
	ParticleView(const SelfRemovalFn& removeSelfFn);

private:
	void OnParticleMove(const gfx::Vector& pos);
	void RemoveSelf();

	virtual void OnDrawImpl(const gfx::Program& program) const = 0;

	glm::mat4 m_transform;
	SelfRemovalFn m_removeSelfFn;
	core::utils::ScopedConnections m_conns;
};
