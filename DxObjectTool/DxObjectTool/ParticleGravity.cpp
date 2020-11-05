#include "stdafx.h"
#include "ParticleGravity.h"
#include "Particle.h"

CParticleGravity::CParticleGravity(const D3DXVECTOR3 & gravity)
	: m_vGravity(gravity)
{
}

void CParticleGravity::updateForce(CParticle * particle, float duration)
{
	if (!particle->hasFiniteMass())	return;
	particle->addForce(m_vGravity * particle->getMass());
}