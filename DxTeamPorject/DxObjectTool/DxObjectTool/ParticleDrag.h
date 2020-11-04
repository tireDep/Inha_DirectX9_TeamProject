#pragma once
#include "ParticleForceGenerator.h"

class CParticleDrag : public CParticleForceGenerator
{
private:
	float m_fK1;
	float m_fK2;
public:
	CParticleDrag(float k1, float k2);
	virtual void updateForce(CParticle* particle, float duration);
};