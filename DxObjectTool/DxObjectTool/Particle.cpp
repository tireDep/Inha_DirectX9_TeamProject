#include "stdafx.h"
#include "Particle.h"

CParticle::CParticle()
{
}

CParticle::~CParticle()
{
}

void CParticle::integrate(float duration)
{
	if (m_finverseMass <= 0.0f) return;

	assert(duration > 0.0);

	m_vPosition = m_vPosition + m_vVelocity * duration;
	
	///
	// 다른 힘이 적용되면 추가할 부분
	///

	D3DXVECTOR3	resultingAcc = m_vAcceleration;
	resultingAcc = resultingAcc + m_vforceAccum * m_finverseMass;

	m_vVelocity = m_vVelocity + resultingAcc * duration;
	m_vVelocity *= powf(m_fDamping, duration);

	clearAccumulatior();
}

void CParticle::setMass(const float mass)
{
	assert(mass != 0);
	m_finverseMass = ((float)1.0) / mass;
}

float CParticle::getMass() const
{
	if (m_finverseMass == 0)
		return FLT_MAX;
	else
		return ((float)1.0) / m_finverseMass;
}

void CParticle::setInverseMass(const float inverseMass)
{
	m_finverseMass = inverseMass;
}

float CParticle::getInverseMass() const
{
	return m_finverseMass;
}

bool CParticle::hasFiniteMass() const
{
	return m_finverseMass >= 0.0f;
}

void CParticle::setDamping(const float damping)
{
	m_fDamping = damping;
}

float CParticle::getDamping() const
{
	return m_fDamping;
}

void CParticle::setPosition(const D3DXVECTOR3 & position)
{
	m_vPosition = position;
}

void CParticle::setPosition(const float x, const float y, const float z)
{
	m_vPosition.x = x;
	m_vPosition.y = y;
	m_vPosition.z = z;
}

void CParticle::getPosition(D3DXVECTOR3 * position) const
{
	*position = m_vPosition;
}

D3DXVECTOR3 CParticle::getPosition() const
{
	return m_vPosition;
}

void CParticle::setVelocity(const D3DXVECTOR3 & velocity)
{
	m_vVelocity = velocity;
}

void CParticle::setVelocity(const float x, const float y, const float z)
{
	m_vVelocity.x = x;
	m_vVelocity.y = y;
	m_vVelocity.z = z;
}

void CParticle::getVelocity(D3DXVECTOR3 * velocity) const
{
	*velocity = m_vVelocity;
}

D3DXVECTOR3 CParticle::getVelocity() const
{
	return m_vVelocity;
}

void CParticle::setAcceleration(const D3DXVECTOR3 & acceleration)
{
	m_vAcceleration = acceleration;
}

void CParticle::setAcceleration(const float x, const float y, const float z)
{
	m_vAcceleration.x = x;
	m_vAcceleration.y = y;
	m_vAcceleration.z = z;
}

void CParticle::getAcceleration(D3DXVECTOR3 * acceleration) const
{
	*acceleration = m_vAcceleration;
}

D3DXVECTOR3 CParticle::getAcceleration() const
{
	return m_vAcceleration;
}

void CParticle::clearAccumulatior()
{
	m_vforceAccum.x = 0.0f;
	m_vforceAccum.y = 0.0f;
	m_vforceAccum.z = 0.0f;
}

void CParticle::addForce(const D3DXVECTOR3 & force)
{
	m_vforceAccum += force;
}