#include "ParticleView.h"

void ParticleView::Observe(Particle& particle)
{
	particle.SubscribeOnMove([this](const gfx::Vector& pos) {
		// TODO: update transform matrix
	});
}
