#pragma once
#include "ParticleForceGenerator.h"
class CParticleDrag : public CParticleForceGenerator
{
private:
	float m_fk1;
	float m_fk2;
public:
	CParticleDrag(float k1, float k2);
	virtual void UpdateForce(CParticle* particle, float duration);
};