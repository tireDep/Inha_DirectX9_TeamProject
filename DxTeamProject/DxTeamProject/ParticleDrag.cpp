#include "stdafx.h"
#include "ParticleDrag.h"
#include "Particle.h"

CParticleDrag::CParticleDrag(float k1, float k2)
	: m_fk1(k1), m_fk2(k2)
{
}

void CParticleDrag::UpdateForce(CParticle * particle, float duration)
{
	D3DXVECTOR3	force;
	particle->GetVelocity(&force);

	float dragCoeff = D3DXVec3Length(&force);
	dragCoeff = m_fk1 * dragCoeff + m_fk2 * dragCoeff * dragCoeff;

	D3DXVec3Normalize(&force, &force);
	force *= -dragCoeff;
	particle->AddForce(force);
}