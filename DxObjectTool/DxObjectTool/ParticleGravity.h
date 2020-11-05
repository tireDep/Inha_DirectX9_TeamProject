#pragma once
#include "ParticleForceGenerator.h"

class CParticleGravity : public CParticleForceGenerator
{
private:
	D3DXVECTOR3		m_vGravity;
public:
	CParticleGravity(const D3DXVECTOR3& gravity);
	virtual void updateForce(CParticle* particle, float duration);
};