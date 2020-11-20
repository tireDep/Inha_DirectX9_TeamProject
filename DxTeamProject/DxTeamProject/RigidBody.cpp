#include "stdafx.h"
#include "RigidBody.h"

CRigidBody::CRigidBody()
{
}
CRigidBody::~CRigidBody()
{
}

// 1..
void CRigidBody::calculateDeriveDate()
{
	D3DXQuaternionNormalize(&m_qOrientation, &m_qOrientation);
	calculateTransformMatrix();
	calculateTransformInertiaTensor();
}

void CRigidBody::calculateTransformMatrix()
{
	D3DXMATRIXA16 matR, matT;
	D3DXMatrixRotationQuaternion(&matR, &m_qOrientation);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matTransformmatrix = matR * matT;
}

// 2..
void CRigidBody::calculateTransformInertiaTensor()
{
	// right hand write ... modify later?
	D3DXMATRIXA16 mat1 = m_matTransformmatrix;
	D3DXMATRIXA16 mat2 = m_matinverseInertiaTensor;

	float t4  = mat1._11 * mat2._11 + mat1._12 * mat2._21 + mat1._13 * mat2._31;
	float t9  = mat1._11 * mat2._12 + mat1._12 * mat2._22 + mat1._13 * mat2._32;
	float t14 = mat1._11 * mat2._13 + mat1._12 * mat2._23 + mat1._13 * mat2._33;
	float t28 = mat1._21 * mat2._11 + mat1._22 * mat2._21 + mat1._23 * mat2._31;
	float t33 = mat1._21 * mat2._12 + mat1._22 * mat2._22 + mat1._23 * mat2._32;
	float t38 = mat1._21 * mat2._13 + mat1._22 * mat2._23 + mat1._23 * mat2._33;
	float t52 = mat1._31 * mat2._11 + mat1._32 * mat2._21 + mat1._33 * mat2._31;
	float t57 = mat1._31 * mat2._12 + mat1._32 * mat2._22 + mat1._33 * mat2._32;
	float t62 = mat1._31 * mat2._13 + mat1._32 * mat2._23 + mat1._33 * mat2._33;

	m_matinverseInertiaTensorWorld._11 = t4  * mat1._11 + t9  * mat1._12 + t14 * mat1._13;
	m_matinverseInertiaTensorWorld._12 = t4  * mat1._21 + t9  * mat1._22 + t14 * mat1._23;
	m_matinverseInertiaTensorWorld._13 = t4  * mat1._31 + t9  * mat1._32 + t14 * mat1._33;
	m_matinverseInertiaTensorWorld._21 = t28 * mat1._11 + t33 * mat1._12 + t38 * mat1._13;
	m_matinverseInertiaTensorWorld._22 = t28 * mat1._21 + t33 * mat1._22 + t38 * mat1._23;
	m_matinverseInertiaTensorWorld._23 = t28 * mat1._31 + t33 * mat1._32 + t38 * mat1._33;
	m_matinverseInertiaTensorWorld._31 = t52 * mat1._11 + t57 * mat1._12 + t62 * mat1._13;
	m_matinverseInertiaTensorWorld._32 = t52 * mat1._21 + t57 * mat1._22 + t62 * mat1._23;
	m_matinverseInertiaTensorWorld._33 = t52 * mat1._31 + t57 * mat1._32 + t62 * mat1._33;
}

// 3..
void CRigidBody::addForce(const D3DXVECTOR3 & force)
{
	m_vforceAccum += force;
	m_isAwake = true;
}
void CRigidBody::clearAccumulators()
{
	m_vforceAccum.x = m_vforceAccum.y = m_vforceAccum.z = 0.0f;
	m_vtorqueAccum.x = m_vtorqueAccum.y = m_vtorqueAccum.z = 0.0f;
}

void CRigidBody::integrate(float duration)
{
	// 5.. right hand
	m_lastFrameAcceleration = m_vAcceleration;
	m_lastFrameAcceleration += (m_vforceAccum * m_finverseMass);
	D3DXVECTOR3 angularAcceleration;
	angularAcceleration.x = m_matinverseInertiaTensorWorld._11 * m_vtorqueAccum.x + m_matinverseInertiaTensorWorld._12 * m_vtorqueAccum.y + m_matinverseInertiaTensorWorld._13 * m_vtorqueAccum.z;
	angularAcceleration.y = m_matinverseInertiaTensorWorld._21 * m_vtorqueAccum.x + m_matinverseInertiaTensorWorld._22 * m_vtorqueAccum.y + m_matinverseInertiaTensorWorld._23 * m_vtorqueAccum.z;
	angularAcceleration.z = m_matinverseInertiaTensorWorld._31 * m_vtorqueAccum.x + m_matinverseInertiaTensorWorld._32 * m_vtorqueAccum.y + m_matinverseInertiaTensorWorld._33 * m_vtorqueAccum.z;
	m_vVelocity += (m_lastFrameAcceleration * duration);
	m_vRotation += (angularAcceleration * duration);
	m_vVelocity *= powf(m_flinearDamping, duration);
	m_vRotation *= powf(m_fangularDamping, duration);
	m_vPosition += (m_vVelocity * duration);
	D3DXQUATERNION q;
	q.w = 0.0f;
	q.x = m_vVelocity.x * duration;
	q.y = m_vVelocity.y * duration;
	q.z = m_vVelocity.z * duration;
	m_qOrientation *= q;
	m_qOrientation.w += q.w * 0.5f;
	m_qOrientation.x += q.x * 0.5f;
	m_qOrientation.y += q.y * 0.5f;
	m_qOrientation.z += q.z * 0.5f;
	calculateDeriveDate();
	clearAccumulators();

	//if (!m_isAwake) return;
	//if (m_canSleep)
	//{
	//	float currentMotion = D3DXVec3LengthSq(&m_vVelocity) + D3DXVec3LengthSq(&m_vRotation);
	//	float bias = powf(0.5, duration);
	//	m_fmotion = bias * m_fmotion + (1 - bias)*currentMotion;
	//	if (m_fmotion < 0.3f)
	//		setAwake(false);
	//	else if (m_fmotion > 10 * 0.3f)
	//		m_fmotion = 10 * 10 * 0.3f;
	//}
}

void CRigidBody::addForceAtPoint(const D3DXVECTOR3 & force, const D3DXVECTOR3 & point)
{
	D3DXVECTOR3	pt = point;
	pt -= m_vPosition;

	m_vforceAccum += force;
	D3DXVECTOR3 tmp;
	D3DXVec3Cross(&tmp, &force, &pt);
	m_vtorqueAccum += tmp;
	m_isAwake = true;
}

void CRigidBody::addForceAtBodyPoint(const D3DXVECTOR3 & force, const D3DXVECTOR3 & point)
{
	//D3DXVECTOR3 pt = getPointInWorldSpace(point);
	//addForceAtPoint(force, pt);
}

// 4..
bool CRigidBody::hasFiniteMass() const
{
	return m_finverseMass >= 0.0f;
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