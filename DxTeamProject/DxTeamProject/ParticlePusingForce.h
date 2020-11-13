#pragma once
#include "ParticleForceGenerator.h"
class CParticlePusingForce : public CParticleForceGenerator
{
private:
	D3DXVECTOR3	m_vDirection;
public:
	CParticlePusingForce(const D3DXVECTOR3 & direction);
	virtual void UpdateForce(CParticle* particle, float duration);
};