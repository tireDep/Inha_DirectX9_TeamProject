#include "stdafx.h"
#include "Particle.h"

CParticle::CParticle()
{
}

CParticle::~CParticle()
{
}

void CParticle::SetMass(const float mass)
{
	assert(mass != 0);
	m_finverseMass = ((float)1.0) / mass;
}

float CParticle::GetMass() const
{
	if (m_finverseMass == 0) { return FLT_MAX; }
	else { return ((float)1.0) / m_finverseMass; }
}

bool CParticle::hasFineteMass() const
{
	return m_finverseMass >=0.0f;
}

void CParticle::SetPosition(const float x, const float y, const float z)
{
	m_vPosition.x = x;
	m_vPosition.y = y;
	m_vPosition.z = z;
}

void CParticle::SetVelocity(const float x, const float y, const float z)
{
	m_vVelocity.x = x;
	m_vVelocity.y = y;
	m_vVelocity.z = z;
}

void CParticle::SetAcceleration(const float x, const float y, const float z)
{
	m_vAcceleration.x = x;
	m_vAcceleration.y = y;
	m_vAcceleration.z = z;
}

void CParticle::GetPosition(D3DXVECTOR3 * position) const
{
	*position = m_vPosition;
}

void CParticle::GetVelocity(D3DXVECTOR3 * velocity) const
{
	*velocity = m_vVelocity;
}

void CParticle::GetAcceleration(D3DXVECTOR3 * acceleration) const
{
	*acceleration = m_vAcceleration;
}

void CParticle::ClearAccumulator()
{
	m_vForceAccum.x = m_vForceAccum.y = m_vForceAccum.z = 0.0f;
}

void CParticle::AddForce(const D3DXVECTOR3 & force)
{
	m_vForceAccum += force;
}

void CParticle::Integrate(float duration)
{
	if (m_finverseMass <= 0.0f) return;
	assert(duration > 0.0f);

	m_vPosition += (m_vVelocity * duration);

	D3DXVECTOR3 resultingAcc = m_vAcceleration;
	resultingAcc += (m_vForceAccum * m_finverseMass);
	m_vVelocity += (resultingAcc * duration);
	m_vVelocity *= pow(m_fdamping, duration);

	ClearAccumulator();
}