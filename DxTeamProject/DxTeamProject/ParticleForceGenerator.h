#pragma once
#include "Particle.h"

class CParticleForceGenerator
{
public:
	virtual void UpdateForce(CParticle *particle, float duration) = 0;
};