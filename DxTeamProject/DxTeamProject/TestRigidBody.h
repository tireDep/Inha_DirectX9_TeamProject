#pragma once
#include "TestForce.h"
#include "TestAngleSet.h"

class CTestRigidBody
{
public:
	CTestRigidBody();
	~CTestRigidBody();
private:
	ID3DXMesh*	m_pMesh;
	D3DMATERIAL9 m_stMtl;

	// linear
	float m_fMass;	// Mass
	Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vPosition, Position);	// Center of mass position
	Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vLinearVelocity, LinearVelocity);	// Linear Velocity
	Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vLinearAccerleration, LinearAccerleration);	// linear Accerleration
	CTestForce sumForces;	// Force

	// rotation
	CTestAngleSet currentOrientation; // Orientation
	Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vAngularVelocity, AngularVelocity); // Angular Velocity
	Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vAngularAccerleration, AngularAccerleration);	// Angular Accerleration
	Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vRotationInertia, RotationInertia);	// Rotation Inertia;
	Synthesize_Pass_by_Ref(D3DXVECTOR3, m_vTorque, Torque);	// Torque;

	// collision
	Synthesize(float, m_fElasticity, Elasticity);	// Elastcity
	Synthesize(float, m_fBoundingSphere, BoundingSphere);	// BoundingSphere Radius

	Synthesize(bool, m_isForceApplied, ForceApplied);
	D3DXMATRIXA16 m_matWorld;
public:
	void setMass(float massValue);
	float getMass();
	void setForce(CTestForce sumExternalForces);
	CTestForce getForce();
	void setCurrentOrientation(CTestAngleSet newOrientation);
	CTestAngleSet getCurrentOrientation();

	void Setup();
	void Update(float duration);
	void Render();
};