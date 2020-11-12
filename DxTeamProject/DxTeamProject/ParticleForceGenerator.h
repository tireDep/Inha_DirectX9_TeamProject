#pragma once

class CParticle;

class CParticleForceGenerator
{
public:
	virtual void UpdateForce(CParticle *particle, float duration) = 0;
};