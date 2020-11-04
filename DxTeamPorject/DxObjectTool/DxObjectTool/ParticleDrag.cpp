#include "stdafx.h"
#include "ParticleDrag.h"
#include "Particle.h"

CParticleDrag::CParticleDrag(float k1, float k2)
	: m_fK1(k1)
	, m_fK2(k2)
{
}

void CParticleDrag::updateForce(CParticle * particle, float duration)
{
	D3DXVECTOR3	force;
	particle->getVelocity(&force);

	float dragCoeff = D3DXVec3Length(&force);
	dragCoeff = m_fK1 * dragCoeff + m_fK2 * dragCoeff * dragCoeff;

	D3DXVec3Normalize(&force, &force);
	force *= -dragCoeff;
	particle->addForce(force);
}