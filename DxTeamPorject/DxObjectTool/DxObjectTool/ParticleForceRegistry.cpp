#include "stdafx.h"
#include "ParticleForceRegistry.h"
#include "Particle.h"
#include "ParticleForceGenerator.h"

CParticleForceRegistry::CParticleForceRegistry()
	: m_vRegistrations(NULL)
{
}

CParticleForceRegistry::~CParticleForceRegistry()
{
	m_vRegistrations.clear();
}

void CParticleForceRegistry::add(CParticle * particle, CParticleForceGenerator * fg)
{
	ParticleForceRegistration registration;
	registration.particle = particle;
	registration.fg = fg;
	m_vRegistrations.push_back(registration);
}

void CParticleForceRegistry::remove(CParticle * particle, CParticleForceGenerator * fg)
{
	/// 추후 구현
}

void CParticleForceRegistry::clear()
{
	/// 추후 구현
}

void CParticleForceRegistry::updateForces(float duration)
{
	Registry::iterator it = m_vRegistrations.begin();
	for (; it != m_vRegistrations.end(); it++)
	{
		it->fg->updateForce(it->particle, duration);
	}
}