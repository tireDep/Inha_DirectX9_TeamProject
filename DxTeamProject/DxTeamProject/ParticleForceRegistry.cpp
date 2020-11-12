#include "stdafx.h"
#include "ParticleForceRegistry.h"
#include "Particle.h"
#include "ParticleForceGenerator.h"

CParticleForceRegistry::CParticleForceRegistry()
{
}

CParticleForceRegistry::~CParticleForceRegistry()
{
}

void CParticleForceRegistry::Add(CParticle * particle, CParticleForceGenerator * fg)
{
	ParticleForceRegistation registration;
	registration.particle = particle;
	registration.fg = fg;
	m_stRegistrations.push_back(registration);
}

void CParticleForceRegistry::Remove(CParticle * particle, CParticleForceGenerator * fg)
{
	// find + erase를 이용해 이후 추가
}

void CParticleForceRegistry::Clear()
{
	m_stRegistrations.clear();
}

void CParticleForceRegistry::UpdateForces(float duration)
{
	/// 이 부분 에러 m_stRegistrations 초기화되버림...
	Registry::iterator it = m_stRegistrations.begin();
	for (; it != m_stRegistrations.end(); it++)
	{
		it->fg->UpdateForce(it->particle, duration);
	}
}