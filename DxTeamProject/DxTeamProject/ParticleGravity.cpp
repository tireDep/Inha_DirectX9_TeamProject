#include "stdafx.h"
#include "ParticleGravity.h"

CParticleGravity::CParticleGravity()
	: m_vGravity(0, -9.81f/10, 0)
{
}

CParticleGravity::CParticleGravity(const D3DXVECTOR3 & gravity)
	: m_vGravity(gravity)
{
}

void CParticleGravity::UpdateForce(CParticle * particle, float duration)
{
	if (!particle->hasFineteMass()) return;
	particle->AddForce(m_vGravity * particle->GetMass());
}