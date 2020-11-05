#pragma once

class CParticle;

class CParticleForceGenerator
{
public:
	virtual void updateForce(CParticle *particle, float duration) = 0;
};