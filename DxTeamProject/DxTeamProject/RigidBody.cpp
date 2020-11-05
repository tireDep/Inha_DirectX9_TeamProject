#include "stdafx.h"
#include "RigidBody.h"
#include "TimeManager.h"

CRigidBody::CRigidBody()
	: m_flinearDamping(0.999f)
	//, m_vAcceleration(0, -9.8f/3, 0)	// 중력
	, m_vVelocity(0, 0, 0)
	, m_vforceAccum(0, 0, 0)
	, m_finverseMass(10.0f)
{
	D3DXMatrixIdentity(&m_matWorld);
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::intergrate(float duration)
{
	if (m_finverseMass <= 0.0f)	return;
	assert(duration > 0.0);

	m_vPosition += (m_vVelocity * duration);

	D3DXVECTOR3	resultingAcc = m_vAcceleration;			
	resultingAcc += (m_vforceAccum * m_finverseMass);
	m_vVelocity += (resultingAcc * duration);
	m_vVelocity *= powf(m_flinearDamping, duration);

	clearAccumulators();
}

void CRigidBody::clearAccumulators()
{
	m_vforceAccum.x = m_vforceAccum.y = m_vforceAccum.z = 0.0f;
}

bool CRigidBody::hasFiniteMass() const
{
	return m_finverseMass >= 0.0f;
}

void CRigidBody::addForce(const D3DXVECTOR3 & force)
{
	m_vforceAccum += force;
}

float CRigidBody::getMass() const
{
	if (m_finverseMass == 0)
		return FLT_MAX;
	else
		return ((float)1.0) / m_finverseMass;
}

void CRigidBody::Setup(D3DXVECTOR3 position, D3DXVECTOR3 acc)
{
	m_vPosition = position;
	m_vAcceleration = acc;
	
	float cubeSize = 0.5f;
	ST_PC_VERTEX v;
	v.c = D3DCOLOR_XRGB(255, 0, 0);
	// front
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);	m_vecVertex.push_back(v);

	// back
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);

	// left
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize);	m_vecVertex.push_back(v);

	// right
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);

	// top
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);

	// bottom
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);
}

void CRigidBody::Update()
{
	intergrate(g_pTimeManager->GetElapsedTime());
	D3DXMatrixTranslation(&m_matWorld, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	if (m_vPosition.y < 0.0f)
		m_finverseMass = 0.0f;
}

void CRigidBody::Render()
{
	//cout << m_vPosition.x << ' ' << m_vPosition.y << ' ' << m_vPosition.z << endl;

	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PC_VERTEX));
}

/// 1105 구현했던 부분 주석 처리
//{
//	void CRigidBody::addForce(const D3DXVECTOR3 & force)
//	{
//		m_vforceAccum += force;
//		m_isAwake = true;
//	}
//
//	void CRigidBody::clearAccumulators()
//	{
//		m_vforceAccum.x = m_vforceAccum.y = m_vforceAccum.z = 0.0f;
//		m_vtorqueAccum.x = m_vtorqueAccum.y = m_vtorqueAccum.z = 0.0f;
//	}
//
//	void CRigidBody::intergrate(float duration)
//	{
//		m_vlastFrameAcceleration = m_vAcceleration;
//		m_vlastFrameAcceleration = m_vlastFrameAcceleration + m_vforceAccum * m_finverseMass;
//		// 주의 !!!!!!!!! 
//		/// 다시 책 살펴보기. 이해한 바와 다르게 구현될수도
//		/// 책에서는 따로 멤버 변수로 받지 않고 내부에서 쓰고 버림(각도라)
//		D3DXVECTOR3 angularAcceleration;
//		D3DXVec3TransformCoord(&angularAcceleration, &m_vtorqueAccum, &m_inverseInertiaTensorWorld);
//		m_vVelocity = m_vVelocity + m_vlastFrameAcceleration * duration;
//		m_vRotation = m_vRotation + angularAcceleration * duration;
//		m_vVelocity *= powf(m_flinearDamping, duration);
//		m_vRotation *= powf(m_fangularDamping, duration);
//		m_vPosition = m_vPosition + m_vVelocity * duration;
//		// 쿼터니언과 벡터의 덧셈 구현이후 다시 밑 주석 풀기
//		// m_qDirection = m_qDirection + m_vRotation * duration;
//
//		clearAccumulators();
//	}
//
//	void CRigidBody::addForceAtPoint(const D3DXVECTOR3 & force, const D3DXVECTOR3 & point)
//	{
//		D3DXVECTOR3 pt = point;
//		pt -= m_vPosition;
//		m_vforceAccum += force;
//
//		// 주의 !!!!!!!!! 
//		/// 외적은 좌표계 달라져서 반대로 곱해야 할 수도 있음. 
//		D3DXVECTOR3	ptCross;
//		D3DXVec3Cross(&ptCross, &pt, &force);
//
//		m_vtorqueAccum += ptCross;
//		m_isAwake = true;
//	}
//
//	void CRigidBody::addForceAtBodyPoint(const D3DXVECTOR3 & force, const D3DXVECTOR3 & point)
//	{
//		D3DXVECTOR3 pt = getPointInLocalSpace(point);
//		addForceAtPoint(force, pt);
//		m_isAwake = true;
//	}
//
//	D3DXVECTOR3 CRigidBody::getPointInLocalSpace(const D3DXVECTOR3 & point) const
//	{
//		// 주의 !!!!!!!!! 
//		/// 다시 책 살펴보기. 이해한 바와 다르게 구현될수도
//		D3DXVECTOR3 pt;
//		D3DXVec3TransformCoord(&pt, &point, &m_matWorld);
//
//		return pt;
//	}
//
//	bool CRigidBody::hasFiniteMass() const
//	{
//		return m_finverseMass >= 0.0f;
//	}
//
//	float CRigidBody::getMass() const
//	{
//		if (m_finverseMass == 0)
//			return FLT_MAX;
//		else
//			return ((float)1.0) / m_finverseMass;
//	}
//
//	void CRigidBody::calculateDerivedData()
//	{
//		/// 쿼터니언 노말라이즈 구현해두기.
//		//m_qDirection.nomailze();
//		/// 추가해두어야 할 기능
//		// Calculate the transform matrix for the body.
//		// 물체의 위치와 방향으로부터 변환 행렬을 만드는 인라인 함수.
//		// Calculate the inertiaTensor in world space.
//		// 사원수에 의해 관성 텐서의 변환을 수행하는 내부 함수.
//	}
//}