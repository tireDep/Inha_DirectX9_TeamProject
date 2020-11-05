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
	
	clearAccumulators();
}

void CRigidBody::addForceAtPoint(const D3DXVECTOR3 & force, const D3DXVECTOR3 & point)
{
	D3DXVECTOR3 pt = point;
	pt -= m_vPosition;
	m_vforceAccum += force;

	// 주의 !!!!!!!!! 
	/// 외적은 좌표계 달라져서 반대로 곱해야 할 수도 있음. 
	D3DXVECTOR3 ptCross;
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