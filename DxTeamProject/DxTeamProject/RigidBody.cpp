#include "stdafx.h"
#include "RigidBody.h"
#include "TimeManager.h"

CRigidBody::CRigidBody()
	: m_flinearDamping(0.999f)
	//, m_vAcceleration(0, -9.8f/3, 0)	// �߷�
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

/// 1105 �����ߴ� �κ� �ּ� ó��
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
//		// ���� !!!!!!!!! 
//		/// �ٽ� å ���캸��. ������ �ٿ� �ٸ��� �����ɼ���
//		/// å������ ���� ��� ������ ���� �ʰ� ���ο��� ���� ����(������)
//		D3DXVECTOR3 angularAcceleration;
//		D3DXVec3TransformCoord(&angularAcceleration, &m_vtorqueAccum, &m_inverseInertiaTensorWorld);
//		m_vVelocity = m_vVelocity + m_vlastFrameAcceleration * duration;
//		m_vRotation = m_vRotation + angularAcceleration * duration;
//		m_vVelocity *= powf(m_flinearDamping, duration);
//		m_vRotation *= powf(m_fangularDamping, duration);
//		m_vPosition = m_vPosition + m_vVelocity * duration;
//		// ���ʹϾ�� ������ ���� �������� �ٽ� �� �ּ� Ǯ��
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
//		// ���� !!!!!!!!! 
//		/// ������ ��ǥ�� �޶����� �ݴ�� ���ؾ� �� ���� ����. 
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
//		// ���� !!!!!!!!! 
//		/// �ٽ� å ���캸��. ������ �ٿ� �ٸ��� �����ɼ���
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
//		/// ���ʹϾ� �븻������ �����صα�.
//		//m_qDirection.nomailze();
//		/// �߰��صξ�� �� ���
//		// Calculate the transform matrix for the body.
//		// ��ü�� ��ġ�� �������κ��� ��ȯ ����� ����� �ζ��� �Լ�.
//		// Calculate the inertiaTensor in world space.
//		// ������� ���� ���� �ټ��� ��ȯ�� �����ϴ� ���� �Լ�.
//	}
//}