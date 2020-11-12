#pragma once
#include "ParticleForceGenerator.h"
class CParticleGravity : public CParticleForceGenerator
{
private:
	D3DXVECTOR3	m_vGravity;
public:
	CParticleGravity();
	CParticleGravity(const D3DXVECTOR3 &gravity);
	virtual void UpdateForce(CParticle* particle, float duration);
};