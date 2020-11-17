#include "stdafx.h"
#include "RigidBody.h"

CRigidBody::CRigidBody()
{
}
CRigidBody::~CRigidBody()
{
}

void CRigidBody::calculateDeriveDate()
{
	//orientation.normalize();
	//_calculateTransformMatrix(m_matTransformMatrix, m_vPosition, orientation);
	//_transformInertiaTensor(inverseInertiaTensorWorld, orientation, inverseInertiaTensor, m_matTransformMatrix);
}

void CRigidBody::integrate(float duration)
{
	if (!m_isAwake) return;

	m_lastFrameAcceleration = m_vAcceleration;
	m_lastFrameAcceleration += (m_vforceAccum * m_finverseMass);
	//D3DXVECTOR3 angularAcceleration = inverseInertiaTensorWorld * m_vtorqueAccum;
	m_vVelocity += (m_lastFrameAcceleration * duration);
	//m_vRotation += (angularAcceleration * duration);
	m_vVelocity *= powf(m_flinearDamping, duration);
	m_vRotation *= powf(m_fangularDamping, duration);
	m_vPosition += (m_vVelocity * duration);
	//orientation += (m_vRotation, duration);
	calculateDeriveDate();
	clearAccumulators();
	if (m_canSleep)
	{
		float currentMotion = D3DXVec3LengthSq(&m_vVelocity) + D3DXVec3LengthSq(&m_vRotation);
		float bias = powf(0.5, duration);
		m_fmotion = bias * m_fmotion + (1 - bias)*currentMotion;
		if (m_fmotion < 0.3f)
			setAwake(false);
		else if (m_fmotion > 10 * 0.3f)
			m_fmotion = 10 * 10 * 0.3f;
	}
}

void CRigidBody::setMass(const float mass)
{
	assert(mass != 0);
	m_finverseMass = ((float)1.0f) / mass;
}

float CRigidBody::getMass() const
{
	if (m_finverseMass == 0)
	{
		return FLT_MAX;
	}
	else
	{
		return ((float)1.0) / m_finverseMass;
	}
}

void CRigidBody::setInverseMass(const float inverseMass)
{
	m_finverseMass = inverseMass;
}

float CRigidBody::getInverseMass() const
{
	return m_finverseMass;
}

bool CRigidBody::hasFiniteMass() const
{
	return m_finverseMass >= 0.0f;
}

void CRigidBody::setDamping(const float linearDamping, const float angularDamping)
{
	m_flinearDamping = linearDamping;
	m_fangularDamping = angularDamping;
}

void CRigidBody::setLinearDamping(const float linearDamping)
{
	m_flinearDamping = linearDamping;
}

float CRigidBody::getLinearDamping() const
{
	return m_flinearDamping;
}

void CRigidBody::setAngularDamping(const float angularDamping)
{
	m_fangularDamping = angularDamping;
}

float CRigidBody::getAngularDamping() const
{
	return m_fangularDamping;
}

void CRigidBody::setPosition(const D3DXVECTOR3 & position)
{
	m_vPosition = position;
}

void CRigidBody::setPosition(const float x, const float y, const float z)
{
	m_vPosition.x = x;
	m_vPosition.y = y;
	m_vPosition.z = z;
}

void CRigidBody::getPosition(D3DXVECTOR3 * position) const
{
	*position = m_vPosition;
}

D3DXVECTOR3 CRigidBody::getPosition() const
{
	return m_vPosition;
}

void CRigidBody::setVelocity(const D3DXVECTOR3 & velocity)
{
	m_vVelocity = velocity;
}

void CRigidBody::setVelocity(const float x, const float y, const float z)
{
	m_vVelocity.x = x;
	m_vVelocity.y = y;
	m_vVelocity.z = z;
}

void CRigidBody::getVelocity(D3DXVECTOR3 * velocity) const
{
	*velocity = m_vVelocity;
}

D3DXVECTOR3 CRigidBody::getVelocity() const
{
	return m_vVelocity;
}

void CRigidBody::addVelocity(const D3DXVECTOR3 & deltaVelocity)
{
	m_vVelocity += deltaVelocity;
}

void CRigidBody::setRotation(const D3DXVECTOR3 & rotation)
{
	m_vRotation = rotation;
}

void CRigidBody::setRotation(const float x, const float y, const float z)
{
	m_vRotation.x = x;
	m_vRotation.y = y;
	m_vRotation.z = z;
}

void CRigidBody::getRotation(D3DXVECTOR3 * rotation) const
{
	*rotation = m_vRotation;
}

D3DXVECTOR3 CRigidBody::getRotation() const
{
	return m_vRotation;
}

void CRigidBody::addRotation(const D3DXVECTOR3 & deltaRotation)
{
	m_vRotation += deltaRotation;
}

void CRigidBody::setAwake(const bool awake)
{
	if (awake)
	{
		m_isAwake = true;
		m_fmotion = 0.3f * 2.0f;
	}
	else
	{
		m_isAwake = false;
		m_vVelocity.x = m_vVelocity.y = m_vVelocity.z = 0.0f;
		m_vRotation.x = m_vRotation.y = m_vRotation.z = 0.0f;
	}
}

void CRigidBody::setCanSleep(const bool canSleep)
{
	m_canSleep = canSleep;
	if (!canSleep && !m_isAwake)
		setAwake();
}

void CRigidBody::getLastFrameAcceleration(D3DXVECTOR3 * linearAcceleration) const
{
	*linearAcceleration = m_lastFrameAcceleration;
}

D3DXVECTOR3 CRigidBody::getLastFrameAcceleration() const
{
	return m_lastFrameAcceleration;
}

void CRigidBody::clearAccumulators()
{
	m_vforceAccum.x = m_vforceAccum.y = m_vforceAccum.z = 0.0f;
	m_vtorqueAccum.x = m_vtorqueAccum.y = m_vtorqueAccum.z = 0.0f;
}

void CRigidBody::addForce(const D3DXVECTOR3 & force)
{
	m_vforceAccum += force;
	m_isAwake = true;
}

void CRigidBody::addForceAtPoint(const D3DXVECTOR3 & force, const D3DXVECTOR3 & point)
{
	D3DXVECTOR3	pt = point;
	pt -= m_vPosition;

	m_vforceAccum += force;
	D3DXVECTOR3 tmp;
	D3DXVec3Cross(&tmp, &pt, &force);
	m_vtorqueAccum += tmp;
	m_isAwake = true;
}

void CRigidBody::addTorque(const D3DXVECTOR3 & torque)
{
	m_vtorqueAccum += torque;
	m_isAwake = true;
}

void CRigidBody::setAcceleration(const D3DXVECTOR3 & acceleration)
{
	m_vAcceleration = acceleration;
}

void CRigidBody::setAcceleration(const float x, const float y, const float z)
{
	m_vAcceleration.x = x;
	m_vAcceleration.y = y;
	m_vAcceleration.z = z;
}

void CRigidBody::getAcceleration(D3DXVECTOR3 * acceleration) const
{
	*acceleration = m_vAcceleration;
}

D3DXVECTOR3 CRigidBody::getAcceleration() const
{
	return m_vAcceleration;
}