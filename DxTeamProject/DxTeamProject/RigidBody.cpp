#include "stdafx.h"
#include "RigidBody.h"

CRigidBody::CRigidBody()
{
}

CRigidBody::~CRigidBody()
{
}

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

void CRigidBody::intergrate(float duration)
{
	m_vlastFrameAcceleration = m_vAcceleration;
	m_vlastFrameAcceleration = m_vlastFrameAcceleration + m_vforceAccum * m_finverseMass;
	// 주의 !!!!!!!!! 
	/// 다시 책 살펴보기. 이해한 바와 다르게 구현될수도
	/// 책에서는 따로 멤버 변수로 받지 않고 내부에서 쓰고 버림(각도라)
	D3DXVECTOR3 angularAcceleration;
	D3DXVec3TransformCoord(&angularAcceleration, &m_vtorqueAccum, &m_inverseInertiaTensorWorld);
	m_vVelocity = m_vVelocity + m_vlastFrameAcceleration * duration;
	m_vRotation = m_vRotation + angularAcceleration * duration;
	m_vVelocity *= powf(m_flinearDamping, duration);
	m_vRotation *= powf(m_fangularDamping, duration);
	m_vPosition = m_vPosition + m_vVelocity * duration;
	// 쿼터니언과 벡터의 덧셈 구현이후 다시 밑 주석 풀기
	// m_qDirection = m_qDirection + m_vRotation * duration;
	
	clearAccumulators();
}

void CRigidBody::addForceAtPoint(const D3DXVECTOR3 & force, const D3DXVECTOR3 & point)
{
	D3DXVECTOR3 pt = point;
	pt -= m_vPosition;
	m_vforceAccum += force;

	// 주의 !!!!!!!!! 
	/// 외적은 좌표계 달라져서 반대로 곱해야 할 수도 있음. 
	D3DXVECTOR3	ptCross;
	D3DXVec3Cross(&ptCross, &pt, &force);

	m_vtorqueAccum += ptCross;
	m_isAwake = true;
}

void CRigidBody::addForceAtBodyPoint(const D3DXVECTOR3 & force, const D3DXVECTOR3 & point)
{
	D3DXVECTOR3 pt = getPointInLocalSpace(point);
	addForceAtPoint(force, pt);
	m_isAwake = true;
}

D3DXVECTOR3 CRigidBody::getPointInLocalSpace(const D3DXVECTOR3 & point) const
{
	// 주의 !!!!!!!!! 
	/// 다시 책 살펴보기. 이해한 바와 다르게 구현될수도
	D3DXVECTOR3 pt;
	D3DXVec3TransformCoord(&pt, &point, &m_matWorld);

	return pt;
}

bool CRigidBody::hasFiniteMass() const
{
	return m_finverseMass >= 0.0f;
}

float CRigidBody::getMass() const
{
	if (m_finverseMass == 0)
		return FLT_MAX;
	else
		return ((float)1.0) / m_finverseMass;
}

void CRigidBody::calculateDerivedData()
{
	/// 쿼터니언 노말라이즈 구현해두기.
	//m_qDirection.nomailze();
	/// 추가해두어야 할 기능
	// Calculate the transform matrix for the body.
	// 물체의 위치와 방향으로부터 변환 행렬을 만드는 인라인 함수.
	// Calculate the inertiaTensor in world space.
	// 사원수에 의해 관성 텐서의 변환을 수행하는 내부 함수.
}