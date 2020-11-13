#include "stdafx.h"
#include "ParticlePusingForce.h"

CParticlePusingForce::CParticlePusingForce(const D3DXVECTOR3 & direction)
{
	m_vDirection = direction;
}

void CParticlePusingForce::UpdateForce(CParticle * particle, float duration)
{
	if (!particle->hasFineteMass()) return;
	particle->AddForce(m_vDirection * particle->GetMass());
}