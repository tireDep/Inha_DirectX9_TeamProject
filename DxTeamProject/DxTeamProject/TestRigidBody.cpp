#include "stdafx.h"
#include "TestRigidBody.h"

CTestRigidBody::CTestRigidBody()
	: m_pMesh(NULL)
	, m_fMass(100)
	, m_vPosition(0, 0, 0)
	, m_vLinearVelocity(0, 0, 0)
	, m_vLinearAccerleration(0, 0, 0)
	, m_vAngularVelocity(0, 0, 0)
	, m_vAngularAccerleration(0, 0, 0)
	, m_vRotationInertia(39.6f, 39.6f, 12.5f)
	, m_vTorque(0, 0, 0)
	, m_fElasticity(0.5f)
	, m_fBoundingSphere(0.68f)
{
	D3DXMatrixIdentity(&m_matWorld);
	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
}

CTestRigidBody::~CTestRigidBody()
{
	SafeRelease(m_pMesh);
}

void CTestRigidBody::setMass(float massValue)
{
	assert(massValue > 0);
	m_fMass = massValue;
}

float CTestRigidBody::getMass()
{
	return m_fMass;
}

void CTestRigidBody::setConstantForce(CTestForce ConstantForce)
{
	constantForce = ConstantForce;
}

CTestForce CTestRigidBody::getConstantForce()
{
	return constantForce;
}

void CTestRigidBody::setImpulseForce(CTestForce ImpulseForce)
{
	impulseForce = ImpulseForce;
}

CTestForce CTestRigidBody::getImpulseForce()
{
	return impulseForce;
}

void CTestRigidBody::setCurrentOrientation(CTestAngleSet newOrientation)
{
	currentOrientation = newOrientation;
}

CTestAngleSet CTestRigidBody::getCurrentOrientation()
{
	return currentOrientation;
}

void CTestRigidBody::Setup()
{
	D3DXCreateBox(g_pD3DDevice, 1, 1, 1, &m_pMesh, NULL);
	m_stMtl.Ambient = GRAY;
	m_stMtl.Diffuse = GRAY;
	m_stMtl.Specular = GRAY;
}

void CTestRigidBody::Update(float duration)
{
	// linear
	assert(m_fMass != 0);

	CTestForce sumForces;
	sumForces.SetForceVector(constantForce.GetForceVector() + impulseForce.GetForceVector());
	m_vLinearAccerleration = sumForces.GetForceVector() / m_fMass;
	m_vLinearVelocity += m_vLinearAccerleration * duration;
	m_vPosition += m_vLinearVelocity * duration;

	D3DXMATRIXA16 totalTransaltion;
	D3DXMatrixTranslation(&totalTransaltion, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	// angular
	D3DXVec3Cross(&m_vTorque, &impulseForce.GetForceLocation(), &impulseForce.GetForceVector());

	m_vAngularAccerleration.x = m_vTorque.x / m_vRotationInertia.x;
	m_vAngularAccerleration.y = m_vTorque.y / m_vRotationInertia.y;
	m_vAngularAccerleration.z = m_vTorque.z / m_vRotationInertia.z;

	m_vAngularVelocity += m_vAngularAccerleration * duration;

	currentOrientation.setXAngle(currentOrientation.getXAngle() + m_vAngularAccerleration.x * duration);
	currentOrientation.setYAngle(currentOrientation.getYAngle() + m_vAngularAccerleration.y * duration);
	currentOrientation.setZAngle(currentOrientation.getZAngle() + m_vAngularAccerleration.z * duration);

	D3DXMATRIXA16 rotationX, rotationY, rotationZ, totalRotation;
	D3DXMatrixRotationX(&rotationX, currentOrientation.getXAngle());
	D3DXMatrixRotationY(&rotationY, currentOrientation.getYAngle());
	D3DXMatrixRotationZ(&rotationZ, currentOrientation.getZAngle());
	D3DXMatrixMultiply(&totalRotation, &rotationX, &rotationY);
	D3DXMatrixMultiply(&totalRotation, &totalRotation, &rotationZ);

	D3DXMatrixMultiply(&m_matWorld, &totalRotation, &totalTransaltion);

	//D3DXVECTOR3 tmp(0.0f, 0.0f, 0.0f);
	//impulseForce.SetForceVector(tmp);
	//impulseForce.SetForceLocation(tmp);
}

void CTestRigidBody::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	//g_pD3DDevice->SetTexture(0, 0);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	m_pMesh->DrawSubset(0);
}